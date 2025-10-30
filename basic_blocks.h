#ifndef BASIC_BLOCKS_H
#define BASIC_BLOCKS_H
#include "tac_generator.h"

typedef struct BasicBlock {
    int id;
    struct Quad* first;
    struct Quad* last;
    struct BasicBlock* next;
} BasicBlock;

typedef struct {
    BasicBlock* head;
    BasicBlock* tail;
    int count;
} BasicBlockList;

BasicBlockList* build_basic_blocks(QuadList* ql);
void basic_blocks_print(BasicBlockList* bbs, FILE* out);
void basic_blocks_write(BasicBlockList* bbs, const char* path);
void basic_blocks_free(BasicBlockList* bbs);

#endif
