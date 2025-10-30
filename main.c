#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tac_generator.h"
#include "basic_blocks.h"
#include "optimizer.h"
#include "symbol_table.h"

/* Forward declarations */
extern int yyparse(void);
extern void* ast_root;
extern int parse_usl_file(const char* filename);
extern SymbolTable* global_symbol_table;
extern int semantic_analysis(ASTNode* root);

int main(int argc, char** argv){
    const char* input = NULL;
    if(argc>1) input = argv[1];
    else input = "input.txt";

    /* Parse the input file */
    int parse_result = parse_usl_file(input);
    
    /* Use the parsed AST */
    ASTNode* ast = (ASTNode*)ast_root;
    
    /* Check if parsing was successful */
    if(parse_result != 0 || ast == NULL) {
        fprintf(stderr, "Parsing failed or no valid AST generated.\n");
        return 1;
    }
    
    printf("\n=== AST (Abstract Syntax Tree) ===\n");
    print_ast_tree(ast, 0);
    printf("\n");

    /* Perform semantic analysis */
    int semantic_result = semantic_analysis(ast);
    if(semantic_result != 0) {
        fprintf(stderr, "Semantic analysis failed. Aborting compilation.\n");
        return 1;
    }

    /* Generate Three Address Code (TAC) */
    QuadList* ql = tac_create();
    generate_tac(ast, ql);
    
    /* Create output directory */
    system("mkdir output 2>nul");
    
    /* Output TAC in quadruple form */
    printf("=== TAC (Three Address Code) in Quadruple Form ===\n");
    tac_print(ql, stdout);
    printf("\n");
    
    /* Write TAC to file */
    tac_write_file(ql,"output/tac.txt");
    
    /* Build basic blocks */
    BasicBlockList* bbs = build_basic_blocks(ql);
    basic_blocks_write(bbs,"output/basic_blocks.txt");
    
    /* Optimize TAC */
    printf("=== Optimization Process ===\n");
    optimize_tac(ql,bbs);
    
    /* Output optimization report with justification */
    optimizer_write_report("output/optimization_log.txt");
    
    /* Read and display optimization report */
    FILE* opt_report = fopen("output/optimization_log.txt", "r");
    if(opt_report) {
        printf("Optimization Report:\n");
        char buffer[256];
        while(fgets(buffer, sizeof(buffer), opt_report)) {
            printf("%s", buffer);
        }
        fclose(opt_report);
        printf("\n");
    }
    
    /* Output optimized TAC */
    printf("=== Optimized TAC in Quadruple Form ===\n");
    tac_print(ql, stdout);
    printf("\n");
    
    tac_write_file(ql,"output/optimized_tac.txt");
    
    /* Print summary */
    printf("=== Compilation Summary ===\n");
    printf("TAC generated: %d quads\n", ql->count);
    printf("Basic blocks: %d\n", bbs->count);
    printf("Optimization report: output/optimization_log.txt\n");
    printf("Original TAC: output/tac.txt\n");
    printf("Optimized TAC: output/optimized_tac.txt\n");
    printf("Basic blocks: output/basic_blocks.txt\n");
    
    /* Cleanup */
    tac_free(ql);
    basic_blocks_free(bbs);
    
    return 0;
}