#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// String representations of node types for printing
const char* ast_node_type_names[] = {
    "PROGRAM",
    "VARIABLE_DECL",
    "PAGE_DEF",
    "URL_PROP",
    "TITLE_PROP",
    "DESC_PROP",
    "TEMPLATE_PROP",
    "ACCESS_PROP",
    "REDIRECT_PROP",
    "SEO_BLOCK",
    "META_TAGS_BLOCK",
    "META_DESC",
    "META_KEYWORDS",
    "GENERATE_CONTENT",
    "IF_STMT",
    "IF_ELSE_STMT",
    "STATEMENT_BLOCK",
    "FUNCTION_CALL",
    "NAVIGATION",
    "LINK",
    "FOOTER",
    "STRING_LITERAL",
    "URL_PATTERN",
    "VARIABLE_REF",
    "IDENTIFIER",
    "NUMBER"
};

ASTNode* create_ast_node(ASTNodeType type, const char* value, int line_number) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for AST node\n");
        exit(1);
    }
    
    node->type = type;
    node->child = NULL;
    node->sibling = NULL;
    node->line_number = line_number;
    
    if (value != NULL) {
        node->value = (char*)malloc(strlen(value) + 1);
        if (node->value == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for AST node value\n");
            free(node);
            exit(1);
        }
        strcpy(node->value, value);
    } else {
        node->value = NULL;
    }
    
    return node;
}

void free_ast_tree(ASTNode* node) {
    if (node == NULL) return;
    
    // Free children first
    free_ast_tree(node->child);
    
    // Free siblings
    free_ast_tree(node->sibling);
    
    // Free value
    if (node->value != NULL) {
        free(node->value);
    }
    
    // Free node itself
    free(node);
}

void print_ast_tree(ASTNode* node, int depth) {
    if (node == NULL) return;
    
    // Print indentation
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    // Print node information with better formatting
    printf("[%s]", ast_node_type_names[node->type]);
    if (node->value) {
        printf(" \"%s\"", node->value);
    }
    printf("\n");
    
    // Print children
    print_ast_tree(node->child, depth + 1);
    
    // Print siblings
    print_ast_tree(node->sibling, depth);
}