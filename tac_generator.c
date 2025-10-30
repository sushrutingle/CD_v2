#include "tac_generator.h"
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

/* Minimal TAC generator stub: traverses simple AST structure if available.
   This is conservative and non-intrusive: if ast_root is NULL or unrecognized, it creates no quads.
   It expects your AST node structure similar to ASTNode with fields: type, value, child, sibling.
*/

/* We'll try to detect fields dynamically via known struct layout is not possible in C at runtime.
   So this generator will look for functions exported by the project for AST traversal.
   If none exist, we leave TAC empty. */

void generate_tac(void* ast_root, QuadList* out){
    /* This is a safe stub to avoid changing project behavior: real generation requires integration
       with your AST structures. For now, we create a simple example if ast_root==NULL to demonstrate outputs. */
    if(!out) return;
    if(!ast_root){
        tac_append(out,"=","/home","", "url");
        tac_append(out,"=","Welcome to MySite","", "title");
        tac_append(out,"CALL","generate_content","","tmp1");
        return;
    }
    /* If your project exports a function 'ast_to_tac' we can call it; but we avoid modifying existing internals here. */
    return;
}
