#include "tac_generator.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

QuadList* tac_create(){
    QuadList* q = (QuadList*)calloc(1,sizeof(QuadList));
    return q;
}
void tac_free(QuadList* ql){
    if(!ql) return;
    Quad* q = ql->head;
    while(q){
        Quad* nx = q->next;
        free(q);
        q = nx;
    }
    free(ql);
}
Quad* tac_append(QuadList* ql, const char* op, const char* a1, const char* a2, const char* res){
    Quad* q = (Quad*)calloc(1,sizeof(Quad));
    strncpy(q->op, op?op:"",31);
    strncpy(q->arg1, a1?a1:"",127);
    strncpy(q->arg2, a2?a2:"",127);
    strncpy(q->res, res?res:"",127);
    q->next = NULL;
    if(!ql->head) ql->head = q;
    else ql->tail->next = q;
    ql->tail = q;
    ql->count++;
    return q;
}
void tac_print(QuadList* ql, FILE* out){
    if(!ql){ fprintf(out,"<no TAC>\n"); return; }
    fprintf(out,"#   OP                      ARG1                             ARG2                             RES\n");
    fprintf(out,"-------------------------------------------------------------------------------------------------------------\n");
    int i=1;
    for(Quad* q=ql->head; q; q=q->next){
        fprintf(out,"%2d  %-22s %-32s %-32s %-20s\n", i, q->op, q->arg1, q->arg2, q->res);
        i++;
    }
}
void tac_write_file(QuadList* ql, const char* path){
    FILE* f = fopen(path,"w");
    if(!f) return;
    tac_print(ql,f);
    fclose(f);
}

/* Forward declaration */
void ast_to_tac(ASTNode* node, QuadList* out, char* result_temp);

/* Helper function to generate a new temporary variable name */
static int temp_counter = 0;
char* new_temp() {
    static char temp_name[32];
    sprintf(temp_name, "t%d", temp_counter++);
    return temp_name;
}

/* Helper function to process AST nodes recursively */
void ast_to_tac(ASTNode* node, QuadList* out, char* result_temp) {
    if (!node) return;
    
    switch (node->type) {
        case AST_PROGRAM:
            // Process children
            for (ASTNode* child = node->child; child; child = child->sibling) {
                ast_to_tac(child, out, NULL);
            }
            break;
            
        case AST_VARIABLE_DECL:
            if (node->value && node->child) {
                char temp[128];
                ast_to_tac(node->child, out, temp);
                tac_append(out, "=", temp, "", node->value);
            }
            break;
            
        case AST_STRING_LITERAL:
            if (result_temp && node->value) {
                strcpy(result_temp, node->value);
            }
            break;
            
        case AST_NUMBER:
            if (result_temp && node->value) {
                strcpy(result_temp, node->value);
            }
            break;
            
        case AST_PAGE_DEF:
            // Process page properties
            for (ASTNode* child = node->child; child; child = child->sibling) {
                ast_to_tac(child, out, NULL);
            }
            break;
            
        case AST_URL_PROP:
        case AST_TITLE_PROP:
        case AST_DESC_PROP:
        case AST_TEMPLATE_PROP:
        case AST_ACCESS_PROP:
            if (node->child) {
                char temp[128];
                ast_to_tac(node->child, out, temp);
                char prop_name[128];
                sprintf(prop_name, "%s_%s", node->value ? node->value : "prop", new_temp());
                tac_append(out, "=", temp, "", prop_name);
            }
            break;
            
        case AST_FUNCTION_CALL:
            if (result_temp && node->value) {
                // For function calls, we generate a CALL operation
                char func_result[128];
                strcpy(func_result, new_temp());
                tac_append(out, "CALL", node->value, "", func_result);
                
                // Process arguments if any
                for (ASTNode* arg = node->child; arg; arg = arg->sibling) {
                    char arg_temp[128];
                    ast_to_tac(arg, out, arg_temp);
                    tac_append(out, "PARAM", arg_temp, "", "");
                }
                
                strcpy(result_temp, func_result);
            }
            break;
            
        case AST_IDENTIFIER:
            if (result_temp && node->value) {
                strcpy(result_temp, node->value);
            }
            break;
            
        default:
            // Process children for other node types
            for (ASTNode* child = node->child; child; child = child->sibling) {
                ast_to_tac(child, out, NULL);
            }
            break;
    }
}

/* Generate TAC from AST root pointer */
void generate_tac(void* ast_root, QuadList* out){
    if (!out) return;
    
    if (!ast_root) {
        // Demo TAC for testing copy propagation
        tac_append(out, "=", "10", "", "x");
        tac_append(out, "=", "x", "", "y");
        tac_append(out, "+", "y", "5", "t0");
        tac_append(out, "=", "t0", "", "z");
        tac_append(out, "=", "z", "", "w");
        tac_append(out, "*", "w", "2", "t1");
        tac_append(out, "=", "t1", "", "result");
        return;
    }
    
    // Reset temp counter
    temp_counter = 0;
    
    // Generate TAC from AST
    ast_to_tac((ASTNode*)ast_root, out, NULL);
}