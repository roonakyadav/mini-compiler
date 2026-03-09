/*
 * compiler.h - Header file for Mini Compiler
 * Contains token definitions, data structures, and function declarations
 */

#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Maximum limits
#define MAX_TOKEN_LENGTH 100
#define MAX_TOKENS 1000
#define MAX_INTERMEDIATE_CODE 1000
#define MAX_LINE_LENGTH 1000
#define MAX_SYMBOLS 100
#define MAX_STATEMENTS 100

// Token types enumeration
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_ASSIGNMENT,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
    int line;
} Token;

// Symbol table entry
typedef struct {
    char name[MAX_TOKEN_LENGTH];
    int line;
    int is_declared;  // 1 if declared/assigned, 0 otherwise
} Symbol;

// Lexical Analyzer functions
void init_lexer(const char* source);
Token get_next_token(void);
void print_token(Token token);
void print_all_tokens(void);
void reset_lexer_position(void);

// Symbol Table functions
void init_symbol_table(void);
void add_symbol(const char* name, int line);
int find_symbol(const char* name);
void print_symbol_table(void);
int symbol_exists(const char* name);

// Parser functions
void init_parser(Token* tokens, int count);
int parse_statement(void);
int parse_expression(void);
int parse_term(void);
int parse_factor(void);
int match(TokenType expected_type);
Token current_token(void);
void consume(TokenType expected_type);
int validate_syntax(void);
int parse_program(void);  // For multiple statements

// Semantic Analyzer functions
void init_semantic_analyzer(Token* tokens, int count);
int analyze_program(void);
void print_semantic_result(void);

// Code Generator functions
void init_codegen(void);
void generate_code(Token* tokens, int count);
void print_intermediate_code(void);
void reset_temp_counter(void);
char* new_temp(void);
void generate_statement_code(int start_token, int end_token);
void generate_program_code(Token* tokens, int count);

// Global variables
extern char source_code[MAX_LINE_LENGTH];
extern Token tokens[MAX_TOKENS];
extern int token_count;
extern int temp_counter;
extern char intermediate_code[MAX_INTERMEDIATE_CODE][MAX_LINE_LENGTH];
extern int code_line_count;
extern Symbol symbol_table[MAX_SYMBOLS];
extern int symbol_count;

#endif // COMPILER_H
