#ifndef GRAPHICS_AST_H
#define GRAPHICS_AST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ast.h"

/**
 * Visualizes the Abstract Syntax Tree using BGI graphics
 * Opens a graphics window and displays the AST in a hierarchical tree layout
 * 
 * @param root Pointer to the root node of the AST
 */
void visualizeAST(ASTNode* root);

#ifdef __cplusplus
}
#endif

#endif // GRAPHICS_AST_H
