#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// String representations of symbol types
const char* symbol_type_names[] = {
    "VARIABLE",
    "PAGE",
    "FUNCTION"
};

SymbolTable* create_symbol_table() {
    SymbolTable* table = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (table == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for symbol table\n");
        exit(1);
    }
    
    table->head = NULL;
    table->count = 0;
    
    return table;
}

void free_symbol_table(SymbolTable* table) {
    if (table == NULL) return;
    
    Symbol* current = table->head;
    while (current != NULL) {
        Symbol* next = current->next;
        
        if (current->name != NULL) {
            free(current->name);
        }
        free(current);
        
        current = next;
    }
    
    free(table);
}

int add_symbol(SymbolTable* table, const char* name, SymbolType type, int line_number) {
    if (table == NULL || name == NULL) {
        return 0; // Failure
    }
    
    // Check if symbol already exists
    Symbol* current = table->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // Symbol already exists, update line number
            current->line_number = line_number;
            return 1; // Success
        }
        current = current->next;
    }
    
    // Create new symbol
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    if (symbol == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for symbol\n");
        return 0; // Failure
    }
    
    symbol->name = (char*)malloc(strlen(name) + 1);
    if (symbol->name == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for symbol name\n");
        free(symbol);
        return 0; // Failure
    }
    
    strcpy(symbol->name, name);
    symbol->type = type;
    symbol->line_number = line_number;
    symbol->next = table->head;
    
    table->head = symbol;
    table->count++;
    
    return 1; // Success
}

void print_symbol_table(SymbolTable* table) {
    if (table == NULL) {
        printf("Symbol table is NULL\n");
        return;
    }
    
    if (table->head == NULL) {
        printf("Symbol table is empty\n");
        return;
    }
    
    printf("Symbol Table (%d symbols):\n", table->count);
    printf("+----------------------+-----------------+------------+\n");
    printf("| %-20s | %-15s | %-10s |\n", "Name", "Type", "Line");
    printf("+----------------------+-----------------+------------+\n");
    
    // Print symbols in reverse order (since we add to head)
    // First, collect all symbols
    Symbol* symbols[1000]; // Assuming max 1000 symbols
    int count = 0;
    
    Symbol* current = table->head;
    while (current != NULL && count < 1000) {
        symbols[count++] = current;
        current = current->next;
    }
    
    // Print in reverse order
    for (int i = count - 1; i >= 0; i--) {
        printf("| %-20s | %-15s | %-10d |\n", 
               symbols[i]->name, 
               symbol_type_names[symbols[i]->type], 
               symbols[i]->line_number);
    }
    
    printf("+----------------------+-----------------+------------+\n");
}
