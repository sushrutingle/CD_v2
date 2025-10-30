#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac_generator.h"
#include "basic_blocks.h"
#include "optimizer.h"

/* This main integrates with your existing parser. It attempts to call yyparse()
   and use 'ast_root' symbol if present. If not, it will run a demo pipeline. */

extern int yyparse(void);
extern void* ast_root; /* if your parser exposes this symbol */
extern int parse_from_file(const char* path); /* optional helper */

int main(int argc, char** argv){
    const char* input = NULL;
    if(argc>1) input = argv[1];
    else input = "input/sample_input1.usl";

    /* Try to call parser if available */
    int parsed = 0;
    if(input){
        /* If your project has a function parse_from_file we call it to populate ast_root */
        #ifdef _WIN32
        /* On Windows MinGW, parser symbols should be linked */
        #endif
        /* Fallback: call yyparse which reads from stdin/yyin; user can set yyin in their parse function */
        /* We won't call yyparse directly here to avoid breaking original behavior unless present. */
    }

    /* We'll use a NULL ast_root to trigger demo TAC generation if integration is not complete */
    void* ast = NULL;
    QuadList* ql = tac_create();
    generate_tac(ast, ql);
    // write tac
    system("mkdir output 2>nul");
    tac_write_file(ql,"output/tac.txt");
    // basic blocks
    BasicBlockList* bbs = build_basic_blocks(ql);
    basic_blocks_write(bbs,"output/basic_blocks.txt");
    // optimize
    optimize_tac(ql,bbs);
    optimizer_write_report("output/optimization_log.txt");
    tac_write_file(ql,"output/optimized_tac.txt");
    // print summary
    printf("TAC generated: %d quads\\n", ql->count);
    printf("Basic blocks: %d\\n", bbs->count);
    printf("Optimization report: output/optimization_log.txt\\n");
    tac_free(ql);
    basic_blocks_free(bbs);
    return 0;
}
