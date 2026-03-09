/*
 * main.c - Main entry point for Mini Compiler
 * Orchestrates all compiler phases: Lexical Analysis, Syntax Analysis, 
 * Semantic Analysis, and Code Generation
 */

#include "compiler.h"

// Global variables
char source_code[MAX_LINE_LENGTH];
Token tokens[MAX_TOKENS];
int token_count = 0;

// Read multiple lines from input file
int read_input_file_multiline(const char* filename) {
    FILE* file = fopen(filename, "r");
   if (file == NULL) {
       printf("Error: Cannot open input file '%s'\n", filename);
       return 0;
    }
    
    // Clear source code buffer
    memset(source_code, 0, MAX_LINE_LENGTH);
    
    char line[MAX_LINE_LENGTH];
    int first_line = 1;
    
    // Read all lines from file
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // Remove trailing newline
        int len = strlen(line);
       if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
       if (!first_line) {
            // Append with newline separator
            strncat(source_code, "\n", MAX_LINE_LENGTH - strlen(source_code) - 1);
        }
        strncat(source_code, line, MAX_LINE_LENGTH - strlen(source_code) - 1);
        first_line = 0;
    }
    
    fclose(file);
   return 1;
}

// Scan all tokens and store them in array
void scan_tokens(void) {
    token_count = 0;
    Token token;
    
    do {
        token = get_next_token();
       if (token_count < MAX_TOKENS) {
            tokens[token_count++] = token;
        }
    } while (token.type != TOKEN_EOF && token.type != TOKEN_ERROR);
}

// Print compilation statistics
void print_compilation_statistics(void) {
  printf("----- COMPILATION STATISTICS -----\n");
  printf("Total tokens processed:      %d\n", token_count);
  printf("Identifiers in symbol table: %d\n", symbol_count);
  printf("Temporary variables used:    %d\n", temp_counter);
  printf("Intermediate code lines:     %d\n", code_line_count);
  printf("\n");
}

int main(int argc, char* argv[]) {
    const char* input_filename = "input.txt";
    
    // Allow custom input file as command line argument
   if (argc > 1) {
        input_filename = argv[1];
    }
    
   printf("=====================================\n");
   printf("        MINI COMPILER STARTED\n");
   printf("=====================================\n\n");
      
   printf("Initializing compiler phases...\n\n");
    
    // Phase 0: Read input file
   if (!read_input_file_multiline(input_filename)) {
       return 1;
    }
    
   printf("----- SOURCE PROGRAM -----\n");
   printf("%s\n\n", source_code);
    
    // Phase 1: Lexical Analysis
   printf("----- LEXICAL ANALYSIS -----\n");
    init_lexer(source_code);
   print_all_tokens();
    
    // Store tokens for later phases
    scan_tokens();
    
    // Check for lexical errors
   if (tokens[token_count - 1].type == TOKEN_ERROR) {
       printf("Lexical Error: Invalid token found\n");
       return 1;
    }
    
    // Phase 2: Symbol Table
   printf("----- SYMBOL TABLE -----\n");
   print_symbol_table();
    
    // Phase 3: Syntax Analysis
   printf("----- SYNTAX ANALYSIS -----\n");
    init_parser(tokens, token_count);
    
   if (parse_program()) {
       printf("Syntax is valid\n\n");
    } else {
       printf("SYNTAX ERROR\n");
      printf("=== COMPILATION FAILED ===\n");
       return 1;
    }
    
    // Phase 4: Semantic Analysis
   printf("----- SEMANTIC ANALYSIS -----\n");
    init_semantic_analyzer(tokens, token_count);
    
   if (analyze_program()) {
       print_semantic_result();
    } else {
       print_semantic_result();
       return 1;
    }
    
    // Phase 5: Intermediate Code Generation
   printf("----- INTERMEDIATE CODE -----\n");
    generate_program_code(tokens, token_count);
   print_intermediate_code();
    
   printf("=====================================\n");
  printf("       COMPILATION SUCCESSFUL\n");
  printf("=====================================\n");
    
  // Print compilation statistics
 print_compilation_statistics();
    
   return 0;
}
