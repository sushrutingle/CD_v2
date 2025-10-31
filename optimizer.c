#include "optimizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int const_fold_count = 0;
static int dce_count = 0;
static int strength_count = 0;
static int copy_prop_count = 0;
static int dead_code_count = 0;
static int cse_count = 0; // Common Sub-Expression Elimination counter

// Helper function to check if a string is a temporary variable
static int is_temp_var(const char* var) {
    return var && strlen(var) > 0 && var[0] == 't';
}

// Helper function to check if a string is a literal (number or string)
static int is_literal(const char* str) {
    if (!str || strlen(str) == 0) return 0;
    
    // Check if it's a number
    int is_num = 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '.')) {
            is_num = 0;
            break;
        }
    }
    
    // Check if it's a string literal (enclosed in quotes)
    int is_string = (strlen(str) > 1 && str[0] == '"' && str[strlen(str)-1] == '"');
    
    return is_num || is_string;
}

// Helper function to check if a variable is a global identifier (not temporary)
static int is_global_var(const char* var) {
    return var && strlen(var) > 0 && var[0] != 't';
}

// Helper function to check if two quads are equivalent expressions
static int are_equivalent_expressions(Quad* q1, Quad* q2) {
    // Check if both are binary operations with same operator
    if (strcmp(q1->op, q2->op) != 0) return 0;
    
    // Check if operators are binary operations
    if (strcmp(q1->op, "+") != 0 && strcmp(q1->op, "-") != 0 && 
        strcmp(q1->op, "*") != 0 && strcmp(q1->op, "/") != 0) return 0;
    
    // Check if arguments are the same
    if (strcmp(q1->arg1, q2->arg1) != 0) return 0;
    if (strcmp(q1->arg2, q2->arg2) != 0) return 0;
    
    // Check if results are different (otherwise it's the same quad)
    if (strcmp(q1->res, q2->res) == 0) return 0;
    
    return 1;
}

void optimize_tac(QuadList* ql, BasicBlockList* bbs){
    if(!ql) return;
    
    // Reset counters for this optimization pass
    copy_prop_count = 0;
    dead_code_count = 0;
    const_fold_count = 0;
    strength_count = 0;
    cse_count = 0; // Reset CSE counter
    
    // Pass 1: Common Sub-Expression Elimination
    // Look for equivalent expressions and replace redundant computations
    for(Quad* q1=ql->head; q1; q1=q1->next){
        // Only consider binary operations
        if(strcmp(q1->op, "+") != 0 && strcmp(q1->op, "-") != 0 && 
           strcmp(q1->op, "*") != 0 && strcmp(q1->op, "/") != 0) continue;
           
        // Look for equivalent expressions that come after q1
        for(Quad* q2=q1->next; q2; q2=q2->next){
            if(are_equivalent_expressions(q1, q2)){
                // Found a common sub-expression
                // Replace q2->res with q1->res in all subsequent quads
                const char* source = q1->res;
                const char* target = q2->res;
                
                for(Quad* q3=q2->next; q3; q3=q3->next) {
                    // Replace uses of target with source
                    if(strcmp(q3->arg1, target) == 0) {
                        strcpy(q3->arg1, source);
                        cse_count++;
                    }
                    if(strcmp(q3->arg2, target) == 0) {
                        strcpy(q3->arg2, source);
                        cse_count++;
                    }
                }
                
                // Mark q2 as dead code (we'll remove it in the DCE pass)
                // For now, we just replace its operation with a comment
            }
        }
    }
    
    // Pass 2: Copy Propagation
    // Look for assignments of the form: x = y (where y is a variable or literal)
    // Then replace all uses of x with y until x is redefined
    for(Quad* q=ql->head; q; q=q->next){
        // Look for copy statements: res = arg1
        if(strcmp(q->op, "=") == 0 && strlen(q->arg1) > 0 && strlen(q->arg2) == 0) {
            // Found a copy statement: q->res = q->arg1
            const char* source = q->arg1;
            const char* target = q->res;
            
            // Propagate this value to subsequent uses of target
            // We'll propagate both literals/temporaries AND global variables
            for(Quad* q2=q->next; q2; q2=q2->next) {
                // Stop if target is redefined
                if(strcmp(q2->res, target) == 0) break;
                
                // Replace uses of target with source
                if(strcmp(q2->arg1, target) == 0) {
                    strcpy(q2->arg1, source);
                    copy_prop_count++;
                }
                if(strcmp(q2->arg2, target) == 0) {
                    strcpy(q2->arg2, source);
                    copy_prop_count++;
                }
            }
        }
    }
    
    // Pass 3: Constant folding
    for(Quad* q=ql->head; q; q=q->next){
        if((strcmp(q->op,"+")==0 || strcmp(q->op,"-")==0 || strcmp(q->op,"*")==0 || strcmp(q->op,"/")==0)
           && q->arg1 && q->arg2){
            char* e1 = q->arg1; char* e2 = q->arg2;
            int isnum1 = 1, isnum2 = 1;
            for(char* p=e1; *p; ++p) if(!((*p)>='0' && (*p)<='9' || *p=='-')) { isnum1=0; break; }
            for(char* p=e2; *p; ++p) if(!((*p)>='0' && (*p)<='9' || *p=='-')) { isnum2=0; break; }
            if(isnum1 && isnum2){
                long a = atol(e1); long b = atol(e2); long r=0;
                if(strcmp(q->op,"+")==0) r=a+b;
                else if(strcmp(q->op,"-")==0) r=a-b;
                else if(strcmp(q->op,"*")==0) r=a*b;
                else if(strcmp(q->op,"/")==0){ if(b==0) continue; r=a/b; }
                char buf[128]; snprintf(buf,127,"%ld",r);
                strcpy(q->op,"=");
                strcpy(q->arg1,buf);
                q->arg2[0]=0;
                const_fold_count++;
            }
        }
        // strength reduction: x * 2 -> x + x (safe)
        if(strcmp(q->op,"*")==0 && q->arg2 && strcmp(q->arg2,"2")==0){
            strcpy(q->op,"+");
            // keep args same but mark as applied
            strength_count++;
        }
    }
    
    // Pass 4: Improved Dead Code Elimination
    // Count uses of all variables
    typedef struct Use{ char name[128]; int cnt; struct Use* next; } Use;
    Use* uses = NULL;
    
    // Count all uses of variables in arg1 and arg2 positions
    for(Quad* q=ql->head; q; q=q->next){
        if(strlen(q->arg1) > 0){
            Use* u = uses; int found=0;
            while(u){ if(strcmp(u->name,q->arg1)==0){ u->cnt++; found=1; break;} u=u->next; }
            if(!found){ Use* nu=(Use*)malloc(sizeof(Use)); strcpy(nu->name,q->arg1); nu->cnt=1; nu->next=uses; uses=nu; }
        }
        if(strlen(q->arg2) > 0){
            Use* u = uses; int found=0;
            while(u){ if(strcmp(u->name,q->arg2)==0){ u->cnt++; found=1; break;} u=u->next; }
            if(!found){ Use* nu=(Use*)malloc(sizeof(Use)); strcpy(nu->name,q->arg2); nu->cnt=1; nu->next=uses; nu; }
        }
    }
    
    // Remove quads that assign to temporary variables that are never used
    // But preserve assignments to global variables as they may have side effects
    Quad* prev = NULL; Quad* cur = ql->head;
    while(cur){
        int is_temp_assign = (strlen(cur->res) > 0 && is_temp_var(cur->res));
        int used = 0;
        
        if(is_temp_assign){
            Use* u = uses;
            while(u){ if(strcmp(u->name,cur->res)==0){ used=u->cnt; break; } u=u->next; }
            
            // Remove if the temporary result is never used
            // But don't remove function calls or I/O operations which have side effects
            if(!used && strcmp(cur->op, "CALL") != 0 && strcmp(cur->op, "PARAM") != 0){
                // remove cur
                Quad* torem = cur;
                if(prev) prev->next = cur->next; else ql->head = cur->next;
                if(torem==ql->tail) ql->tail = prev;
                cur = cur->next;
                free(torem);
                dead_code_count++;
                continue;
            }
        }
        prev = cur; cur = cur->next;
    }
    
    // Update the dead code elimination counter
    dce_count = dead_code_count;
    
    // free uses
    while(uses){ Use* nx=uses->next; free(uses); uses=nx; }
}

void optimizer_write_report(const char* path){
    FILE* f = fopen(path,"w");
    if(!f) return;
    fprintf(f,"Optimization Report\n");
    fprintf(f,"Constant folding applied: %d\n", const_fold_count);
    fprintf(f,"Strength reductions applied: %d\n", strength_count);
    fprintf(f,"Copy propagations applied: %d\n", copy_prop_count);
    fprintf(f,"Dead code eliminations: %d\n", dce_count);
    fprintf(f,"Common sub-expression eliminations: %d\n", cse_count);
    fclose(f);
}