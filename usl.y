%{
/*
 * URL-based Specification Language (USL) Parser
 * YACC Specification File for USL Compiler
 * 
 * This file defines the syntax and grammar rules for USL
 * and builds an Abstract Syntax Tree (AST) for semantic analysis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol_table.h"

/* External functions from lexer */
extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern void print_lexical_error_table();
extern void print_token_table();
extern void reset_lexer();

/* Global variables */
ASTNode* ast_root = NULL;
SymbolTable* global_symbol_table = NULL;
int parse_error_count = 0;
int last_error_line = -1;  // Track the line number of the last error to avoid duplicates

/* Function prototypes */
void yyerror(const char* s);
void print_parse_tree(ASTNode* node, int depth);
void print_parse_tree_helper(ASTNode* node, int depth, int is_last[], int parent_depth);
int semantic_analysis(ASTNode* root);

%}

/* YACC Declarations */
%union {
    int int_val;
    char* string_val;
    struct ASTNode* ast_node;
}

/* Token declarations with types */
%token <string_val> IDENTIFIER STRING_LITERAL VARIABLE_REF URL_PATTERN
%token <int_val> NUMBER
%token IF ELSE URL TITLE DESCRIPTION TEMPLATE ACCESS SEO META_TAGS
%token NAVIGATION LINKS FOOTER TEXT GENERATE_CONTENT REDIRECT KEYWORDS FUNCTION
%token ASSIGN LBRACE RBRACE LPAREN RPAREN COMMA COLON DOT NEWLINE
%token ERROR_TOKEN

/* Non-terminal types */
%type <ast_node> program statement_list statement variable_declaration
%type <ast_node> page_definition page_body page_property_list page_property
%type <ast_node> seo_block meta_tags_block meta_tag_list meta_tag
%type <ast_node> generate_content_block generate_statement_list generate_statement
%type <ast_node> navigation_block footer_block link_list link
%type <ast_node> expression string_expression function_call argument_list
%type <ast_node> conditional_statement statement_block
%type <string_val> identifier

/* Operator precedence and associativity */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%left COMMA
%right ASSIGN
%left DOT

/* Start symbol */
%start program

%%

/* Grammar Rules */

program:
    statement_list {
        $$ = create_ast_node(AST_PROGRAM, NULL, yylineno);
        $$->child = $1;
        ast_root = $$;
        printf("Parsing completed successfully.\n");
    }
    | /* empty */ {
        $$ = create_ast_node(AST_PROGRAM, NULL, yylineno);
        ast_root = $$;
    }
    ;

statement_list:
    statement {
        $$ = $1;
    }
    | statement_list statement {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            ASTNode* current = $1;
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = $2;
            $$ = $1;
        }
    }
    ;

statement:
    variable_declaration {
        $$ = $1;
    }
    | page_definition {
        $$ = $1;
    }
    | navigation_block {
        $$ = $1;
    }
    | footer_block {
        $$ = $1;
    }
    ;

variable_declaration:
    identifier ASSIGN expression {
        $$ = create_ast_node(AST_VARIABLE_DECL, $1, yylineno);
        $$->child = $3;
        
        /* Add to symbol table */
        if (global_symbol_table) {
            add_symbol(global_symbol_table, $1, SYMBOL_VARIABLE, yylineno);
        }
    }
    ;

page_definition:
    identifier LBRACE page_body RBRACE {
        $$ = create_ast_node(AST_PAGE_DEF, $1, yylineno);
        $$->child = $3;
        
        /* Add page to symbol table */
        if (global_symbol_table) {
            add_symbol(global_symbol_table, $1, SYMBOL_PAGE, yylineno);
        }
    }
    ;

page_body:
    page_property_list {
        $$ = $1;
    }
    | /* empty */ {
        $$ = NULL;
    }
    ;

page_property_list:
    page_property {
        $$ = $1;
    }
    | page_property_list page_property {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            ASTNode* current = $1;
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = $2;
            $$ = $1;
        }
    }
    ;

page_property:
    URL ASSIGN string_expression {
        $$ = create_ast_node(AST_URL_PROP, "url", yylineno);
        $$->child = $3;
    }
    | TITLE ASSIGN expression {
        $$ = create_ast_node(AST_TITLE_PROP, "title", yylineno);
        $$->child = $3;
    }
    | DESCRIPTION ASSIGN expression {
        $$ = create_ast_node(AST_DESC_PROP, "description", yylineno);
        $$->child = $3;
    }
    | TEMPLATE ASSIGN STRING_LITERAL {
        $$ = create_ast_node(AST_TEMPLATE_PROP, "template", yylineno);
        $$->child = create_ast_node(AST_STRING_LITERAL, $3, yylineno);
    }
    | ACCESS ASSIGN STRING_LITERAL {
        $$ = create_ast_node(AST_ACCESS_PROP, "access", yylineno);
        $$->child = create_ast_node(AST_STRING_LITERAL, $3, yylineno);
    }
    | REDIRECT ASSIGN STRING_LITERAL {
        $$ = create_ast_node(AST_REDIRECT_PROP, "redirect", yylineno);
        $$->child = create_ast_node(AST_STRING_LITERAL, $3, yylineno);
    }
    | seo_block {
        $$ = $1;
    }
    | generate_content_block {
        $$ = $1;
    }
    ;

seo_block:
    SEO LBRACE meta_tags_block RBRACE {
        $$ = create_ast_node(AST_SEO_BLOCK, "seo", yylineno);
        $$->child = $3;
    }
    ;

meta_tags_block:
    META_TAGS LBRACE meta_tag_list RBRACE {
        $$ = create_ast_node(AST_META_TAGS_BLOCK, "meta_tags", yylineno);
        $$->child = $3;
    }
    ;

meta_tag_list:
    meta_tag {
        $$ = $1;
    }
    | meta_tag_list meta_tag {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            ASTNode* current = $1;
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = $2;
            $$ = $1;
        }
    }
    ;

meta_tag:
    DESCRIPTION ASSIGN expression {
        $$ = create_ast_node(AST_META_DESC, "description", yylineno);
        $$->child = $3;
    }
    | KEYWORDS ASSIGN expression {
        $$ = create_ast_node(AST_META_KEYWORDS, "keywords", yylineno);
        $$->child = $3;
    }
    ;

generate_content_block:
    GENERATE_CONTENT LBRACE generate_statement_list RBRACE {
        $$ = create_ast_node(AST_GENERATE_CONTENT, "generate_content", yylineno);
        $$->child = $3;
    }
    ;

generate_statement_list:
    generate_statement {
        $$ = $1;
    }
    | generate_statement_list generate_statement {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            ASTNode* current = $1;
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = $2;
            $$ = $1;
        }
    }
    ;

generate_statement:
    variable_declaration {
        $$ = $1;
    }
    | function_call {
        $$ = $1;
    }
    | conditional_statement {
        $$ = $1;
    }
    | page_property {
        $$ = $1;
    }
    ;

conditional_statement:
    IF expression COLON statement_block %prec LOWER_THAN_ELSE {
        $$ = create_ast_node(AST_IF_STMT, "if", yylineno);
        $$->child = $2;
        $2->sibling = $4;
    }
    | IF expression COLON statement_block ELSE COLON statement_block {
        $$ = create_ast_node(AST_IF_ELSE_STMT, "if_else", yylineno);
        $$->child = $2;
        $2->sibling = $4;
        $4->sibling = $7;
    }
    ;

statement_block:
    generate_statement_list {
        $$ = create_ast_node(AST_STATEMENT_BLOCK, "block", yylineno);
        $$->child = $1;
    }
    ;

function_call:
    identifier LPAREN argument_list RPAREN {
        $$ = create_ast_node(AST_FUNCTION_CALL, $1, yylineno);
        $$->child = $3;
    }
    | identifier LPAREN RPAREN {
        $$ = create_ast_node(AST_FUNCTION_CALL, $1, yylineno);
    }
    ;

argument_list:
    expression {
        $$ = $1;
    }
    | argument_list COMMA expression {
        if ($1 == NULL) {
            $$ = $3;
        } else {
            ASTNode* current = $1;
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = $3;
            $$ = $1;
        }
    }
    ;

navigation_block:
    NAVIGATION LBRACE LINKS LBRACE link_list RBRACE RBRACE {
        $$ = create_ast_node(AST_NAVIGATION, "navigation", yylineno);
        $$->child = $5;
    }
    ;

link_list:
    link {
        $$ = $1;
    }
    | link_list link {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            ASTNode* current = $1;
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = $2;
            $$ = $1;
        }
    }
    ;

link:
    identifier ASSIGN STRING_LITERAL {
        $$ = create_ast_node(AST_LINK, $1, yylineno);
        $$->child = create_ast_node(AST_STRING_LITERAL, $3, yylineno);
    }
    ;

footer_block:
    FOOTER LBRACE TEXT ASSIGN expression RBRACE {
        $$ = create_ast_node(AST_FOOTER, "footer", 0);
        $$->child = $5;
    }
    ;

expression:
    string_expression {
        $$ = $1;
    }
    | VARIABLE_REF {
        $$ = create_ast_node(AST_VARIABLE_REF, $1, 0);
    }
    | function_call {
        $$ = $1;
    }
    | identifier {
        $$ = create_ast_node(AST_IDENTIFIER, $1, 0);
    }
    ;

string_expression:
    STRING_LITERAL {
        $$ = create_ast_node(AST_STRING_LITERAL, $1, 0);
    }
    | URL_PATTERN {
        $$ = create_ast_node(AST_URL_PATTERN, $1, 0);
    }
    ;

identifier:
    IDENTIFIER {
        $$ = strdup($1);
    }
    ;


%%

/* User Code Section */

void yyerror(const char* s) {
    // Avoid duplicate error messages for the same line
    if (last_error_line == yylineno) {
        return;
    }
    
    last_error_line = yylineno;
    
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
    
    // Provide additional context about the error
    if (yytext && strlen(yytext) > 0) {
        fprintf(stderr, "Error near token: '%s'\n", yytext);
        
        // Provide specific guidance based on common error patterns
        if (strcmp(s, "syntax error") == 0) {
            // Try to guess what might be missing based on the current token
            if (strcmp(yytext, "{") == 0) {
                fprintf(stderr, "Possible issue: Missing closing '}' or incorrect block structure\n");
            } else if (strcmp(yytext, "}") == 0) {
                fprintf(stderr, "Possible issue: Mismatched braces or unexpected closing brace\n");
            } else if (strcmp(yytext, "=") == 0) {
                fprintf(stderr, "Possible issue: Missing value after assignment operator\n");
            } else if (strcmp(yytext, ";") == 0) {
                fprintf(stderr, "Possible issue: Unexpected semicolon (USL uses newlines for statement separation)\n");
            } else {
                fprintf(stderr, "Possible issues: Missing required syntax element or incorrect token usage\n");
            }
        }
    } else {
        fprintf(stderr, "Error at end of input - possible incomplete statement\n");
    }
    
    parse_error_count++;
}

void print_parse_tree_helper(ASTNode* node, int depth, int is_last[], int parent_depth) {
    if (node == NULL) return;
    
    /* Print tree structure with ASCII characters */
    for (int i = 0; i < depth; i++) {
        if (i == depth - 1) {
            /* Last level - print branch */
            if (is_last[i]) {
                printf("+-- ");
            } else {
                printf("|-- ");
            }
        } else {
            /* Previous levels - print vertical line or space */
            if (is_last[i]) {
                printf("    ");
            } else {
                printf("|   ");
            }
        }
    }
    
    /* Print node information */
    printf("%s", ast_node_type_names[node->type]);
    if (node->value) {
        printf(" [%s]", node->value);
    }
    printf("\n");
    
    /* Update is_last array for children */
    int new_is_last[100];
    for (int i = 0; i <= depth; i++) {
        new_is_last[i] = is_last[i];
    }
    
    /* Print children */
    if (node->child) {
        ASTNode* child = node->child;
        while (child != NULL) {
            new_is_last[depth + 1] = (child->sibling == NULL);
            print_parse_tree_helper(child, depth + 1, new_is_last, depth);
            child = child->sibling;
        }
    }
}

void print_parse_tree(ASTNode* node, int depth) {
    if (node == NULL) return;
    
    int is_last[100] = {0};
    is_last[0] = 1;
    
    /* Print root node */
    printf("%s", ast_node_type_names[node->type]);
    if (node->value) {
        printf(" [%s]", node->value);
    }
    printf("\n");
    
    /* Print children */
    if (node->child) {
        ASTNode* child = node->child;
        while (child != NULL) {
            is_last[1] = (child->sibling == NULL);
            print_parse_tree_helper(child, 1, is_last, 0);
            child = child->sibling;
        }
    }
}

int parse_usl_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return -1;
    }
    
    yyin = file;
    
    /* Reset lexer state and error counters */
    reset_lexer();
    
    /* Initialize symbol table */
    global_symbol_table = create_symbol_table();
    
    printf("Starting parse of %s...\n", filename);
    
    int result = yyparse();
    
    fclose(file);
    
    /* Print token table first */
    print_token_table();
    
    /* Print lexical errors */
    print_lexical_error_table();
    
    if (result == 0 && parse_error_count == 0) {
        printf("\nParsing completed successfully!\n");
        printf("\n");
        printf("==========================================\n");
        printf("    Abstract Syntax Tree\n");
        printf("==========================================\n");
        print_parse_tree(ast_root, 0);
        
        printf("\n");
        printf("==========================================\n");
        printf("    Symbol Table\n");
        printf("==========================================\n");
        print_symbol_table(global_symbol_table);
        
        /* Perform semantic analysis */
        printf("\n");
        printf("==========================================\n");
        printf("    Semantic Analysis\n");
        printf("==========================================\n");
        int semantic_result = semantic_analysis(ast_root);
        
        return semantic_result;
    } else {
        printf("\nParsing failed with %d errors.\n", parse_error_count);
        return -1;
    }
}

/* Main function for standalone parser testing */
#ifdef STANDALONE_PARSER
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <usl_file>\n", argv[0]);
        return 1;
    }
    
    int result = parse_usl_file(argv[1]);
    
    /* Cleanup */
    if (global_symbol_table) {
        free_symbol_table(global_symbol_table);
    }
    if (ast_root) {
        free_ast_tree(ast_root);
    }
    
    return (result == 0) ? 0 : 1;
}
#endif