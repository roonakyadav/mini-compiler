/*
 * parser.c - Syntax Analyzer Implementation
 * Validates grammar rules and builds parse tree structure
 */

#include "compiler.h"

// Global variables for parser
static Token* token_stream = NULL;
static int token_count_local = 0;
static int current_pos = 0;

// Initialize parser with token stream
void init_parser(Token* tokens, int count) {
    token_stream = tokens;
    token_count_local = count;
    current_pos = 0;
}

// Get current token
Token current_token(void) {
    if (current_pos < token_count_local) {
        return token_stream[current_pos];
    }
    
    // Return EOF token if past end
    Token eof_token;
    eof_token.type = TOKEN_EOF;
    strcpy(eof_token.value, "");
    eof_token.line = 1;
    return eof_token;
}

// Advance to next token
static void advance(void) {
    if (current_pos < token_count_local) {
        current_pos++;
    }
}

// Match current token against expected type
int match(TokenType expected_type) {
    Token current = current_token();
    if (current.type == expected_type) {
        advance();
        return 1;
    }
    return 0;
}

// Consume token or report error
void consume(TokenType expected_type) {
    Token current = current_token();
    if (current.type != expected_type) {
        printf("Syntax Error: Expected ");
        switch (expected_type) {
            case TOKEN_IDENTIFIER:
                printf("identifier");
                break;
            case TOKEN_NUMBER:
                printf("number");
                break;
            case TOKEN_OPERATOR:
                printf("operator");
                break;
            case TOKEN_ASSIGNMENT:
                printf("assignment operator");
                break;
            default:
                printf("token");
        }
        printf(", got '%s' instead\n", current.value);
        exit(1);
    }
    advance();
}

/*
 * Grammar Rules Implementation:
 * 
 * Statement → id = Expression
 * Expression → Expression + Term | Expression - Term | Term
 * Term → Term * Factor | Term / Factor | Factor
 * Factor → id | number
 */

// Parse Factor → id | number
int parse_factor(void) {
    Token current = current_token();
    
    if (current.type == TOKEN_IDENTIFIER) {
        match(TOKEN_IDENTIFIER);
        return 1;
    }
    
    if (current.type == TOKEN_NUMBER) {
        match(TOKEN_NUMBER);
        return 1;
    }
    
    // Error: expected factor
    printf("Syntax Error in Factor: expected identifier or number, got '%s'\n", current.value);
    return 0;
}

// Parse Term → Term * Factor | Term / Factor | Factor
int parse_term(void) {
    if (!parse_factor()) {
        return 0;
    }
    
    // Handle left recursion: Term → Term * Factor | Term / Factor
    Token current = current_token();
    while (current.type == TOKEN_OPERATOR && 
           (strcmp(current.value, "*") == 0 || strcmp(current.value, "/") == 0)) {
        
        match(TOKEN_OPERATOR);
        
        if (!parse_factor()) {
            return 0;
        }
        
        current = current_token();
    }
    
    return 1;
}

// Parse Expression → Expression + Term | Expression - Term | Term
int parse_expression(void) {
    if (!parse_term()) {
        return 0;
    }
    
    // Handle left recursion: Expression → Expression + Term | Expression - Term
    Token current = current_token();
    while (current.type == TOKEN_OPERATOR && 
           (strcmp(current.value, "+") == 0 || strcmp(current.value, "-") == 0)) {
        
        match(TOKEN_OPERATOR);
        
        if (!parse_term()) {
            return 0;
        }
        
        current = current_token();
    }
    
    return 1;
}

// Parse Statement → id = Expression
int parse_statement(void) {
    // Expect identifier (variable name)
    Token current = current_token();
    if (current.type != TOKEN_IDENTIFIER) {
        printf("Syntax Error: Expected variable name, got '%s'\n", current.value);
        return 0;
    }
    
    match(TOKEN_IDENTIFIER);
    
    // Expect assignment operator
    consume(TOKEN_ASSIGNMENT);
    
    
    // Parse the expression
   if (!parse_expression()) {
       return 0;
    }
    
   return 1;
}

// Validate entire token stream (single statement)
int validate_syntax(void) {
  return parse_statement();
}

/*
 * Parse multiple statements (program)
 * Supports: statement statement ...
 */
int parse_program(void) {
    int statement_count = 0;
    
    // Parse statements until EOF or error
    while (current_token().type != TOKEN_EOF) {
      if (!parse_statement()) {
          return 0;  // Syntax error in statement
        }
        statement_count++;
        
        // Check for more statements
      if (current_token().type == TOKEN_EOF) {
            break;
        }
    }
    
  return statement_count > 0;
}
