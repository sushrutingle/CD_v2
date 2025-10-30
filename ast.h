#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AST Node Types
typedef enum {
    AST_PROGRAM,
    AST_VARIABLE_DECL,
    AST_PAGE_DEF,
    AST_URL_PROP,
    AST_TITLE_PROP,
    AST_DESC_PROP,
    AST_TEMPLATE_PROP,
    AST_ACCESS_PROP,
    AST_REDIRECT_PROP,
    AST_SEO_BLOCK,
    AST_META_TAGS_BLOCK,
    AST_META_DESC,
    AST_META_KEYWORDS,
    AST_GENERATE_CONTENT,
    AST_IF_STMT,
    AST_IF_ELSE_STMT,
    AST_STATEMENT_BLOCK,
    AST_FUNCTION_CALL,
    AST_NAVIGATION,
    AST_LINK,
    AST_FOOTER,
    AST_STRING_LITERAL,
    AST_URL_PATTERN,
    AST_VARIABLE_REF,
    AST_IDENTIFIER,
    AST_NUMBER
} ASTNodeType;

// String representations of node types for printing
extern const char* ast_node_type_names[];

// AST Node Structure
typedef struct ASTNode {
    ASTNodeType type;
    char* value;
    int line_number;  // Line number where this node appears in source
    struct ASTNode* child;
    struct ASTNode* sibling;
} ASTNode;

// Function prototypes
ASTNode* create_ast_node(ASTNodeType type, const char* value, int dummy);
void free_ast_tree(ASTNode* node);
void print_ast_tree(ASTNode* node, int depth);

// Note: For graphical AST visualization, include "graphics_ast.h" and call visualizeAST()
// This requires linking with WinBGIm library (see README.md for compilation instructions)

#endif // AST_H