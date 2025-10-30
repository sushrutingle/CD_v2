#ifndef TAC_GENERATOR_H
#define TAC_GENERATOR_H
#include <stdio.h>

typedef struct Quad {
    char op[32];
    char arg1[128];
    char arg2[128];
    char res[128];
    struct Quad* next;
} Quad;

typedef struct {
    Quad* head;
    Quad* tail;
    int count;
} QuadList;

QuadList* tac_create();
void tac_free(QuadList* ql);
Quad* tac_append(QuadList* ql, const char* op, const char* a1, const char* a2, const char* res);
void tac_print(QuadList* ql, FILE* out);
void tac_write_file(QuadList* ql, const char* path);

/* generate TAC from AST root pointer (uses your ASTNode type) */
void generate_tac(void* ast_root, QuadList* out);

#endif
