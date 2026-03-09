/*
 * codegen.c - Intermediate Code Generator Implementation
 * Generates three-address code from parsed expressions
 */

#include "compiler.h"

// Global variables for code generation
int temp_counter = 0;
char intermediate_code[MAX_INTERMEDIATE_CODE][MAX_LINE_LENGTH];
int code_line_count = 0;

// Reset temporary variable counter
void reset_temp_counter(void) {
    temp_counter = 0;
}

// Generate a new temporary variable name
char* new_temp(void) {
    static char temp_name[MAX_TOKEN_LENGTH];
    sprintf(temp_name, "t%d", ++temp_counter);
    return temp_name;
}

// Add a line to intermediate code
static void add_code_line(const char* code) {
    if (code_line_count < MAX_INTERMEDIATE_CODE) {
        strncpy(intermediate_code[code_line_count], code, MAX_LINE_LENGTH - 1);
        intermediate_code[code_line_count][MAX_LINE_LENGTH - 1] = '\0';
        code_line_count++;
    }
}

// Forward declarations for recursive parsing
static void parse_expression_codegen(void);
static void parse_term_codegen(void);
static void parse_factor_codegen(void);

// Store the result of expression parsing
static char result_buffer[MAX_TOKEN_LENGTH];

// Get current token for codegen (uses parser's position tracking)
extern Token current_token(void);
extern int match(TokenType expected_type);

// Parse Factor → id | number
static void parse_factor_codegen(void) {
    Token current = current_token();
    
    if (current.type == TOKEN_IDENTIFIER) {
        strcpy(result_buffer, current.value);
        match(TOKEN_IDENTIFIER);
        return;
    }
    
    if (current.type == TOKEN_NUMBER) {
        strcpy(result_buffer, current.value);
        match(TOKEN_NUMBER);
        return;
    }
    
    // Error case
    printf("Error in factor during code generation\n");
    exit(1);
}

// Parse Term → Term * Factor | Term / Factor | Factor
static void parse_term_codegen(void) {
    // Parse first factor
    parse_factor_codegen();
    char left_operand[MAX_TOKEN_LENGTH];
    strcpy(left_operand, result_buffer);
    
    // Check for * or / operators
    Token current = current_token();
    while (current.type == TOKEN_OPERATOR && 
           (strcmp(current.value, "*") == 0 || strcmp(current.value, "/") == 0)) {
        
        char op[2];
        strcpy(op, current.value);
        match(TOKEN_OPERATOR);
        
        // Parse next factor
        parse_factor_codegen();
        char right_operand[MAX_TOKEN_LENGTH];
        strcpy(right_operand, result_buffer);
        
        // Generate temporary variable and code
        char* temp = new_temp();
        char code_line[MAX_LINE_LENGTH];
        sprintf(code_line, "%s = %s %s %s", temp, left_operand, op, right_operand);
        add_code_line(code_line);
        
        // Result is now the temporary variable
        strcpy(left_operand, temp);
        
        current = current_token();
    }
    
    // Final result of term
    strcpy(result_buffer, left_operand);
}

// Parse Expression → Expression + Term | Expression - Term | Term
static void parse_expression_codegen(void) {
    // Parse first term
    parse_term_codegen();
    char left_operand[MAX_TOKEN_LENGTH];
    strcpy(left_operand, result_buffer);
    
    // Check for + or - operators
    Token current = current_token();
    while (current.type == TOKEN_OPERATOR && 
           (strcmp(current.value, "+") == 0 || strcmp(current.value, "-") == 0)) {
        
        char op[2];
        strcpy(op, current.value);
        match(TOKEN_OPERATOR);
        
        // Parse next term
        parse_term_codegen();
        char right_operand[MAX_TOKEN_LENGTH];
        strcpy(right_operand, result_buffer);
        
        // Generate temporary variable and code
        char* temp = new_temp();
        char code_line[MAX_LINE_LENGTH];
        sprintf(code_line, "%s = %s %s %s", temp, left_operand, op, right_operand);
        add_code_line(code_line);
        
        // Result is now the temporary variable
        strcpy(left_operand, temp);
        
        current = current_token();
    }
    
    // Final result of expression
    strcpy(result_buffer, left_operand);
}

// Main code generation function
void generate_code(Token* tokens, int count) {
    // Initialize parser with tokens
    init_parser(tokens, count);
    
    // Reset code generation state
    reset_temp_counter();
    code_line_count = 0;
    
    // Parse statement: id = Expression
    Token current = current_token();
    char variable_name[MAX_TOKEN_LENGTH];
    
    if (current.type != TOKEN_IDENTIFIER) {
        printf("Error: Expected variable name\n");
        exit(1);
    }
    
    strcpy(variable_name, current.value);
    match(TOKEN_IDENTIFIER);
    
    // Expect assignment operator
    if (current_token().type != TOKEN_ASSIGNMENT) {
        printf("Error: Expected assignment operator\n");
        exit(1);
    }
    match(TOKEN_ASSIGNMENT);
    
    // Generate code for expression
    parse_expression_codegen();
    
    // Generate final assignment
    char final_code[MAX_LINE_LENGTH];
    sprintf(final_code, "%s = %s", variable_name, result_buffer);
    add_code_line(final_code);
}

// Print all generated intermediate code
void print_intermediate_code(void) {
    printf("Intermediate Code:\n");
    for (int i = 0; i < code_line_count; i++) {
        printf("%s\n", intermediate_code[i]);
    }
    printf("\n");
}

/*
 * Generate intermediate code for a single statement
 * Resets parser position and generates three-address code for one assignment
 */
void generate_statement_code(int start_token, int end_token) {
    (void)start_token;
    (void)end_token;
    // This function can be used to generate code for specific token ranges
    // For now, we use the existing generate_code which handles full parsing
}

/*
 * Generate intermediate code for multiple statements
 * Processes all tokens and generates three-address code for each statement
 */
void generate_program_code(Token* tokens, int count) {
    init_parser(tokens, count);
   reset_temp_counter();
    code_line_count = 0;
    
    // Process each statement
    while (current_token().type != TOKEN_EOF) {
        Token current = current_token();
        char variable_name[MAX_TOKEN_LENGTH];
        
      if (current.type != TOKEN_IDENTIFIER) {
          printf("Error: Expected variable name\n");
           exit(1);
        }
        
       strcpy(variable_name, current.value);
        match(TOKEN_IDENTIFIER);
        
      if (current_token().type != TOKEN_ASSIGNMENT) {
          printf("Error: Expected assignment operator\n");
           exit(1);
        }
        match(TOKEN_ASSIGNMENT);
        
        // Generate code for expression using internal functions
        parse_expression_codegen();
        
        // Generate final assignment
        char final_code[MAX_LINE_LENGTH];
        sprintf(final_code, "%s = %s", variable_name, result_buffer);
       add_code_line(final_code);
        
      if (current_token().type == TOKEN_EOF) {
            break;
        }
    }
}
