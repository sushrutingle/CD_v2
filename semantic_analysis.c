#include "ast.h"
#include "symbol_table.h"
#include <stdio.h>
#include <string.h>

/* Forward declarations of validation functions */
int validate_variable_declaration(ASTNode* node);
int validate_page_definition(ASTNode* node);
int validate_function_call(ASTNode* node);
int validate_conditional_statement(ASTNode* node);
int validate_navigation_block(ASTNode* node);
int validate_footer_block(ASTNode* node);

/*
 * Semantic analysis function
 * Converts CFG to Semantic Grammar by validating AST structure,
 * checking variable declarations, page definitions, function calls,
 * and conditional statements according to USL language rules.
 */
int semantic_analysis(ASTNode* root) {
    if (root == NULL) {
        fprintf(stderr, "Error: Empty AST provided to semantic analysis\n");
        return -1;
    }

    int error_count = 0;
    
    // Validate program structure
    if (root->type != AST_PROGRAM) {
        fprintf(stderr, "Error: Root node must be a program\n");
        return -1;
    }

    // Traverse the AST and perform semantic checks
    ASTNode* current = root->child;
    while (current != NULL) {
        switch (current->type) {
            case AST_VARIABLE_DECL:
                error_count += validate_variable_declaration(current);
                break;
            case AST_PAGE_DEF:
                error_count += validate_page_definition(current);
                break;
            case AST_FUNCTION_CALL:
                error_count += validate_function_call(current);
                break;
            case AST_IF_STMT:
            case AST_IF_ELSE_STMT:
                error_count += validate_conditional_statement(current);
                break;
            case AST_NAVIGATION:
                error_count += validate_navigation_block(current);
                break;
            case AST_FOOTER:
                error_count += validate_footer_block(current);
                break;
            default:
                // Other node types don't require specific semantic validation
                break;
        }
        current = current->sibling;
    }

    if (error_count == 0) {
        printf("Semantic analysis completed successfully.\n");
        return 0; // Success
    } else {
        printf("Semantic analysis failed with %d errors.\n", error_count);
        return -1; // Failure
    }
}

/*
 * Validates a variable declaration node
 * Checks that the variable name is valid and not already declared
 */
int validate_variable_declaration(ASTNode* node) {
    if (node == NULL || node->type != AST_VARIABLE_DECL) {
        return 1; // Error
    }
    
    // Check if variable already exists in symbol table
    // In a full implementation, this would check the actual symbol table
    // For now, we're just validating the structure
    if (node->value == NULL) {
        fprintf(stderr, "Error: Variable declaration missing name at line %d\n", node->line_number);
        return 1;
    }
    
    // Check that the variable has a value expression
    if (node->child == NULL) {
        fprintf(stderr, "Error: Variable '%s' declaration missing value expression\n", node->value);
        return 1;
    }
    
    return 0; // No errors
}

/*
 * Validates a page definition node
 * Checks that the page has required properties like URL
 */
int validate_page_definition(ASTNode* node) {
    if (node == NULL || node->type != AST_PAGE_DEF) {
        return 1; // Error
    }
    
    if (node->value == NULL) {
        fprintf(stderr, "Error: Page definition missing name at line %d\n", node->line_number);
        return 1;
    }
    
    // Check that page has at least a URL property
    ASTNode* prop = node->child;
    int has_url = 0;
    while (prop != NULL) {
        if (prop->type == AST_URL_PROP) {
            has_url = 1;
            break;
        }
        prop = prop->sibling;
    }
    
    if (!has_url) {
        fprintf(stderr, "Warning: Page '%s' should have a URL property\n", node->value);
        // Not treating this as an error since it might be intentional
    }
    
    return 0; // No errors
}

/*
 * Validates a function call node
 * Checks that the function name is valid and has proper arguments
 */
int validate_function_call(ASTNode* node) {
    if (node == NULL || node->type != AST_FUNCTION_CALL) {
        return 1; // Error
    }
    
    if (node->value == NULL) {
        fprintf(stderr, "Error: Function call missing function name at line %d\n", node->line_number);
        return 1;
    }
    
    // For get_product_details and get_post_details, check they have parameters
    if ((strcmp(node->value, "get_product_details") == 0 || 
         strcmp(node->value, "get_post_details") == 0) && 
        node->child == NULL) {
        fprintf(stderr, "Error: Function '%s' requires a parameter\n", node->value);
        return 1;
    }
    
    return 0; // No errors
}

/*
 * Validates a conditional statement node
 * Checks that the condition is valid and blocks are properly structured
 */
int validate_conditional_statement(ASTNode* node) {
    if (node == NULL || (node->type != AST_IF_STMT && node->type != AST_IF_ELSE_STMT)) {
        return 1; // Error
    }
    
    // Check condition expression
    if (node->child == NULL) {
        fprintf(stderr, "Error: If statement missing condition\n");
        return 1;
    }
    
    // Check then block
    if (node->child->sibling == NULL) {
        fprintf(stderr, "Error: If statement missing then block\n");
        return 1;
    }
    
    // For if-else, check else block
    if (node->type == AST_IF_ELSE_STMT && node->child->sibling->sibling == NULL) {
        fprintf(stderr, "Error: If-else statement missing else block\n");
        return 1;
    }
    
    return 0; // No errors
}

/*
 * Validates a navigation block
 * Checks that links are properly defined
 */
int validate_navigation_block(ASTNode* node) {
    if (node == NULL || node->type != AST_NAVIGATION) {
        return 1; // Error
    }
    
    // Navigation block should have child links
    if (node->child == NULL) {
        fprintf(stderr, "Warning: Navigation block is empty\n");
        // Not treating this as an error since it might be intentional
    }
    
    return 0; // No errors
}

/*
 * Validates a footer block
 * Checks that footer has text content
 */
int validate_footer_block(ASTNode* node) {
    if (node == NULL || node->type != AST_FOOTER) {
        return 1; // Error
    }
    
    // Footer should have text content
    if (node->child == NULL) {
        fprintf(stderr, "Error: Footer block missing text content\n");
        return 1;
    }
    
    return 0; // No errors
}