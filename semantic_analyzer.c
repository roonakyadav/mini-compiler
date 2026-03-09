/*
 * semantic_analyzer.c - Semantic Analyzer Implementation
 * Checks if identifiers used in expressions exist in the symbol table
 */

#include "compiler.h"

// Global variables for semantic analysis
static int semantic_errors = 0;
static Token* current_tokens = NULL;
static int token_count_local = 0;
static int current_pos = 0;

// Initialize semantic analyzer
void init_semantic_analyzer(Token* tokens, int count) {
    current_tokens = tokens;
    token_count_local = count;
    current_pos = 0;
    semantic_errors = 0;
}

// Get current token
static Token get_current_token(void) {
   if (current_pos < token_count_local) {
       return current_tokens[current_pos];
    }
    
    Token eof_token;
    eof_token.type = TOKEN_EOF;
    strcpy(eof_token.value, "");
    eof_token.line = 1;
   return eof_token;
}

// Advance to next token
static void advance_token(void) {
   if (current_pos < token_count_local) {
        current_pos++;
    }
}

// Check if identifier exists in symbol table
static void check_identifier(const char* name) {
   if (!symbol_exists(name)) {
       printf("Semantic Error: Undefined identifier '%s'\n", name);
        semantic_errors++;
    }
}

// Parse factor for semantic analysis
static void semantic_factor(void) {
    Token current = get_current_token();
    
   if (current.type == TOKEN_IDENTIFIER) {
        // Check if identifier is defined
        check_identifier(current.value);
        advance_token();
    } else if (current.type == TOKEN_NUMBER) {
        advance_token();
    }
}

// Parse term for semantic analysis
static void semantic_term(void) {
    semantic_factor();
    
    Token current = get_current_token();
    while (current.type == TOKEN_OPERATOR && 
           (strcmp(current.value, "*") == 0 || strcmp(current.value, "/") == 0)) {
        advance_token();
        semantic_factor();
        current = get_current_token();
    }
}

// Parse expression for semantic analysis
static void semantic_expression(void) {
    semantic_term();
    
    Token current = get_current_token();
    while (current.type == TOKEN_OPERATOR && 
           (strcmp(current.value, "+") == 0 || strcmp(current.value, "-") == 0)) {
        advance_token();
        semantic_term();
        current = get_current_token();
    }
}

// Analyze a single statement
static void semantic_statement(void) {
    Token current = get_current_token();
    
    // First identifier is being assigned (will be added to symbol table)
   if (current.type == TOKEN_IDENTIFIER) {
        // This is a declaration/assignment, add to symbol table if not exists
       if (!symbol_exists(current.value)) {
            add_symbol(current.value, 1);
        }
        advance_token();
    }
    
    // Skip assignment operator
   if (get_current_token().type == TOKEN_ASSIGNMENT) {
        advance_token();
    }
    
    // Analyze the expression
    semantic_expression();
}

// Perform semantic analysis on entire program
int analyze_program(void) {
    semantic_errors = 0;
    
    // Process all statements
    while (get_current_token().type != TOKEN_EOF) {
        semantic_statement();
        
       if (get_current_token().type == TOKEN_EOF) {
            break;
        }
    }
    
   return semantic_errors == 0;
}

// Print semantic analysis result
void print_semantic_result(void) {
   if (semantic_errors == 0) {
       printf("Semantic Analysis: All identifiers are properly defined\n");
    } else {
       printf("Semantic Analysis: %d error(s) found\n", semantic_errors);
    }
   printf("\n");
}
