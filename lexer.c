/*
 * lexer.c - Lexical Analyzer Implementation
 * Converts source code into tokens
 */

#include "compiler.h"
#include <ctype.h>

// Global variables for lexer
static char input_buffer_local[MAX_LINE_LENGTH];
static int position = 0;
static int length = 0;

// Symbol table (defined here, declared in header)
Symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

// Initialize the lexer with source code
void init_lexer(const char* source) {
    // Copy source to buffer
    strncpy(input_buffer_local, source, MAX_LINE_LENGTH - 1);
    input_buffer_local[MAX_LINE_LENGTH - 1] = '\0';
    length = strlen(input_buffer_local);
    position = 0;
}

// Skip whitespace characters
static void skip_whitespace(void) {
    while (position < length && isspace(input_buffer_local[position])) {
        position++;
    }
}

// Skip comment (starts with //)
static void skip_comment(void) {
    // Skip until end of line or end of input
    while (position < length && input_buffer_local[position] != '\n') {
        position++;
    }
}

// Read an identifier or keyword
static Token read_identifier(void) {
    Token token;
    int i = 0;
    
    // Read alphanumeric characters and underscores
    while (position < length && 
           (isalnum(input_buffer_local[position]) || input_buffer_local[position] == '_')) {
        if (i < MAX_TOKEN_LENGTH - 1) {
            token.value[i++] = input_buffer_local[position];
        }
        position++;
    }
    token.value[i] = '\0';
    token.type = TOKEN_IDENTIFIER;
    token.line = 1;
    
    // Add to symbol table if not already present
    if (find_symbol(token.value) == -1) {
        add_symbol(token.value, 1);
    }
    
    return token;
}

// Read a number
static Token read_number(void) {
    Token token;
    int i = 0;
    
    // Read digits
    while (position < length && isdigit(input_buffer_local[position])) {
        if (i < MAX_TOKEN_LENGTH - 1) {
            token.value[i++] = input_buffer_local[position];
        }
        position++;
    }
    token.value[i] = '\0';
    token.type = TOKEN_NUMBER;
    token.line = 1;
    
    return token;
}

// Get the next token from input
Token get_next_token(void) {
    Token token;
    
    // Skip whitespace and comments
    while (1) {
        skip_whitespace();
        
        // Check for end of input
        if (position >= length) {
            token.type = TOKEN_EOF;
            strcpy(token.value, "");
            token.line = 1;
            return token;
        }
        
        // Check for comment start (//)
        if (position +1 < length && 
            input_buffer_local[position] == '/' && 
            input_buffer_local[position + 1] == '/') {
            skip_comment();
            continue;  // Continue to skip whitespace after comment
        }
        
        break;  // No more whitespace or comments
    }
    
    char current_char = input_buffer_local[position];
    
    // Check for assignment operator (=)
    if (current_char == '=') {
        token.type = TOKEN_ASSIGNMENT;
        token.value[0] = '=';
        token.value[1] = '\0';
        token.line = 1;
        position++;
        return token;
    }
    
    // Check for arithmetic operators (+, -, *, /)
    if (current_char == '+' || current_char == '-' || 
        current_char == '*' || current_char == '/') {
        token.type = TOKEN_OPERATOR;
        token.value[0] = current_char;
        token.value[1] = '\0';
        token.line = 1;
        position++;
        return token;
    }
    
    // Check for identifiers (starts with letter or underscore)
    if (isalpha(current_char) || current_char == '_') {
        return read_identifier();
    }
    
    // Check for numbers
    if (isdigit(current_char)) {
        return read_number();
    }
    
    // Unknown character - error
    token.type = TOKEN_ERROR;
    token.value[0] = current_char;
    token.value[1] = '\0';
    token.line = 1;
    position++;
    
    return token;
}

// Print a single token in readable format
void print_token(Token token) {
    switch (token.type) {
        case TOKEN_IDENTIFIER:
            printf("IDENTIFIER(%s)\n", token.value);
            break;
        case TOKEN_NUMBER:
            printf("NUMBER(%s)\n", token.value);
            break;
        case TOKEN_OPERATOR:
            printf("OPERATOR(%s)\n", token.value);
            break;
        case TOKEN_ASSIGNMENT:
            printf("ASSIGNMENT\n");
            break;
        case TOKEN_EOF:
            printf("EOF\n");
            break;
        case TOKEN_ERROR:
            printf("ERROR: Unexpected character '%s'\n", token.value);
            break;
    }
}

// Reset lexer position for re-scanning
void reset_lexer_position(void) {
    position = 0;
}

// Scan through all tokens and print them
void print_all_tokens(void) {
    printf("Tokens:\n");
    
    // Reset lexer position
    position = 0;
    
    Token token;
    do {
        token = get_next_token();
        if (token.type != TOKEN_EOF) {
            print_token(token);
        }
    } while (token.type != TOKEN_EOF);
    
    printf("\n");
    
    // Reset position again for parser
    position = 0;
}

/*
 * Symbol Table Implementation
 */

// Initialize symbol table
void init_symbol_table(void) {
    symbol_count = 0;
}

// Add a symbol to the symbol table
void add_symbol(const char* name, int line) {
   if (symbol_count < MAX_SYMBOLS) {
        strncpy(symbol_table[symbol_count].name, name, MAX_TOKEN_LENGTH - 1);
        symbol_table[symbol_count].name[MAX_TOKEN_LENGTH -1] = '\0';
        symbol_table[symbol_count].line = line;
        symbol_table[symbol_count].is_declared = 1;
        symbol_count++;
    }
}

// Find a symbol in the symbol table, returns index or -1 if not found
int find_symbol(const char* name) {
    for (int i = 0; i < symbol_count; i++) {
       if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Check if a symbol exists in the symbol table
int symbol_exists(const char* name) {
    return find_symbol(name) != -1;
}

// Print the symbol table
void print_symbol_table(void) {
   printf("Symbol Table:\n");
   printf("%-20s %-10s %s\n", "Name", "Line", "Status");
   printf("%-20s %-10s %s\n", "----", "----", "------");
    
    for (int i = 0; i < symbol_count; i++) {
       printf("%-20s %-10d %s\n", 
               symbol_table[i].name, 
               symbol_table[i].line,
               symbol_table[i].is_declared ? "Declared" : "Used");
    }
   printf("\n");
}
