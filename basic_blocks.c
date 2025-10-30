#include "basic_blocks.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

BasicBlockList* build_basic_blocks(QuadList* ql){
    BasicBlockList* list = (BasicBlockList*)calloc(1,sizeof(BasicBlockList));
    if(!ql || !ql->head) return list;
    Quad* cur = ql->head;
    int id=0;
    while(cur){
        BasicBlock* bb = (BasicBlock*)calloc(1,sizeof(BasicBlock));
        bb->id = ++id;
        bb->first = cur;
        // find end: either end of list or a 'GOTO' or 'IF_TRUE' etc. we treat next as new block
        Quad* it = cur;
        while(it){
            if(strcmp(it->op,"GOTO")==0 || strcmp(it->op,"IF_TRUE")==0 || strcmp(it->op,"IF_FALSE")==0){
                bb->last = it;
                it = it->next;
                break;
            }
            if(it->next==NULL){ bb->last = it; it = NULL; break; }
            if(strcmp(it->next->op,"LABEL")==0){ bb->last = it; it = it->next; break; }
            it = it->next;
        }
        if(!list->head) list->head = bb; else list->tail->next = bb;
        list->tail = bb; list->count++;
        cur = it;
    }
    return list;
}

void basic_blocks_print(BasicBlockList* bbs, FILE* out){
    if(!bbs || !bbs->head){ fprintf(out,"<no basic blocks>\n"); return; }
    fprintf(out,"=== Basic Blocks (%d) ===\n", bbs->count);
    for(BasicBlock* b=bbs->head; b; b=b->next){
        fprintf(out,"Block B%d:\n", b->id);
        Quad* q = b->first;
        while(q){
            if(q->op[0]==0) break;
            fprintf(out,"  %s %s %s -> %s\n", q->op, q->arg1[0]?q->arg1:"-", q->arg2[0]?q->arg2:"-", q->res[0]?q->res:"-");
            if(q==b->last) break;
            q = q->next;
        }
    }
}

void basic_blocks_write(BasicBlockList* bbs, const char* path){
    FILE* f = fopen(path,"w");
    if(!f) return;
    basic_blocks_print(bbs,f);
    fclose(f);
}

void basic_blocks_free(BasicBlockList* bbs){
    BasicBlock* b = bbs->head;
    while(b){ BasicBlock* nx = b->next; free(b); b = nx; }
    free(bbs);
}
