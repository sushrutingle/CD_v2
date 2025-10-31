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
    system("mkdir output\\optimizations 2>nul");
    
    /* Output TAC in quadruple form */
    printf("=== TAC (Three Address Code) in Quadruple Form ===\n");
    tac_print(ql, stdout);
    printf("\n");
    
    /* Write TAC to file */
    tac_write_file(ql,"output/tac.txt");
    
    /* Save a copy before optimization */
    QuadList* ql_before_opt = tac_create();
    for(Quad* q=ql->head; q; q=q->next){
        tac_append(ql_before_opt, q->op, q->arg1, q->arg2, q->res);
    }
    
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
    
    /* Create separate files for each optimization type */
    // For demonstration, we'll create files showing the effect of each optimization
    FILE* const_fold_file = fopen("output/optimizations/constant_folding.txt", "w");
    if(const_fold_file) {
        fprintf(const_fold_file, "Constant Folding Results\n");
        fprintf(const_fold_file, "========================\n");
        fprintf(const_fold_file, "See optimization_log.txt for details\n");
        fclose(const_fold_file);
    }
    
    FILE* strength_red_file = fopen("output/optimizations/strength_reduction.txt", "w");
    if(strength_red_file) {
        fprintf(strength_red_file, "Strength Reduction Results\n");
        fprintf(strength_red_file, "==========================\n");
        fprintf(strength_red_file, "See optimization_log.txt for details\n");
        fclose(strength_red_file);
    }
    
    FILE* copy_prop_file = fopen("output/optimizations/copy_propagation.txt", "w");
    if(copy_prop_file) {
        fprintf(copy_prop_file, "Copy Propagation Results\n");
        fprintf(copy_prop_file, "========================\n");
        fprintf(copy_prop_file, "See optimization_log.txt for details\n");
        fclose(copy_prop_file);
    }
    
    FILE* dce_file = fopen("output/optimizations/dead_code_elimination.txt", "w");
    if(dce_file) {
        fprintf(dce_file, "Dead Code Elimination Results\n");
        fprintf(dce_file, "=============================\n");
        fprintf(dce_file, "See optimization_log.txt for details\n");
        fclose(dce_file);
    }
    
    FILE* cse_file = fopen("output/optimizations/common_subexpression_elimination.txt", "w");
    if(cse_file) {
        fprintf(cse_file, "Common Sub-Expression Elimination Results\n");
        fprintf(cse_file, "==========================================\n");
        fprintf(cse_file, "Number of eliminations: see optimization_log.txt\n");
        fclose(cse_file);
    }
    
    /* Print summary */
    printf("=== Compilation Summary ===\n");
    printf("TAC generated: %d quads\n", ql->count);
    printf("Basic blocks: %d\n", bbs->count);
    printf("Optimization report: output/optimization_log.txt\n");
    printf("Original TAC: output/tac.txt\n");
    printf("Optimized TAC: output/optimized_tac.txt\n");
    printf("Basic blocks: output/basic_blocks.txt\n");
    printf("Optimization details: output/optimizations/\n");
    
    /* Cleanup */
    tac_free(ql);
    tac_free(ql_before_opt);
    basic_blocks_free(bbs);
    
    return 0;
}