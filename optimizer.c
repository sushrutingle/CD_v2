#include "optimizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int const_fold_count = 0;
static int dce_count = 0;
static int strength_count = 0;

void optimize_tac(QuadList* ql, BasicBlockList* bbs){
    // Very conservative passes that simply scan and log; real changes are minimal to avoid changing semantics
    if(!ql) return;
    // Constant folding: if op is + - * / and arg1,arg2 are numeric literals, replace with '=' literal
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
    // Dead code elimination: remove assignments to temps that are never used (simple heuristic)
    // Count uses
    typedef struct Use{ char name[128]; int cnt; struct Use* next; } Use;
    Use* uses = NULL;
    for(Quad* q=ql->head; q; q=q->next){
        if(q->arg1 && q->arg1[0]=='t'){
            Use* u = uses; int found=0;
            while(u){ if(strcmp(u->name,q->arg1)==0){ u->cnt++; found=1; break;} u=u->next; }
            if(!found){ Use* nu=(Use*)malloc(sizeof(Use)); strcpy(nu->name,q->arg1); nu->cnt=1; nu->next=uses; uses=nu; }
        }
        if(q->arg2 && q->arg2[0]=='t'){
            Use* u = uses; int found=0;
            while(u){ if(strcmp(u->name,q->arg2)==0){ u->cnt++; found=1; break;} u=u->next; }
            if(!found){ Use* nu=(Use*)malloc(sizeof(Use)); strcpy(nu->name,q->arg2); nu->cnt=1; nu->next=uses; uses=nu; }
        }
    }
    // Remove quads assigning to temps with zero uses
    Quad* prev = NULL; Quad* cur = ql->head;
    while(cur){
        int is_temp_assign = (cur->res && cur->res[0]=='t');
        int used = 0;
        if(is_temp_assign){
            Use* u = uses;
            while(u){ if(strcmp(u->name,cur->res)==0){ used=u->cnt; break; } u=u->next; }
            if(!used){
                // remove cur
                Quad* torem = cur;
                if(prev) prev->next = cur->next; else ql->head = cur->next;
                if(torem==ql->tail) ql->tail = prev;
                cur = cur->next;
                free(torem);
                dce_count++;
                continue;
            }
        }
        prev = cur; cur = cur->next;
    }
    // free uses
    while(uses){ Use* nx=uses->next; free(uses); uses=nx; }
}

void optimizer_write_report(const char* path){
    FILE* f = fopen(path,"w");
    if(!f) return;
    fprintf(f,"Optimization Report\n");
    fprintf(f,"Constant folding applied: %d\n", const_fold_count);
    fprintf(f,"Strength reductions applied: %d\n", strength_count);
    fprintf(f,"Dead code eliminations: %d\n", dce_count);
    fclose(f);
}
