#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "tac_generator.h"
#include "basic_blocks.h"

void optimize_tac(QuadList* ql, BasicBlockList* bbs);
void optimizer_write_report(const char* path);

#endif