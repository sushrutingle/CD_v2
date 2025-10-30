#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol types
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_PAGE,
    SYMBOL_FUNCTION
} SymbolType;

// String representations of symbol types
extern const char* symbol_type_names[];

// Symbol structure
typedef struct Symbol {
    char* name;
    SymbolType type;
    int line_number;
    struct Symbol* next;
} Symbol;

// Symbol table structure
typedef struct SymbolTable {
    Symbol* head;
    int count;
} SymbolTable;

// Function prototypes
SymbolTable* create_symbol_table();
void free_symbol_table(SymbolTable* table);
int add_symbol(SymbolTable* table, const char* name, SymbolType type, int line_number);
void print_symbol_table(SymbolTable* table);

#endif // SYMBOL_TABLE_H