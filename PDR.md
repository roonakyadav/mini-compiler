# Mini Compiler Project — Product Design Report (PDR)

## 1. Project Title

**Mini Compiler for Simple Expression Language**

A complete implementation demonstrating fundamental compiler phases.

---

## 2. Objective

Design and implement a mini compiler in C that processes a simple programming language containing:

- Variable assignments
- Arithmetic expressions with +, -, *, / operators
- Multiple statements per program
- Comments (lines starting with //)

The compiler demonstrates **five core phases** of compilation:

1. **Lexical Analysis** - Tokenizing source code
2. **Syntax Analysis** - Validating grammar structure
3. **Semantic Analysis** - Checking identifier usage
4. **Intermediate Code Generation** - Producing three-address code
5. **Symbol Table Management** - Tracking identifiers

The system reads input from text files and generates formatted output showing all compilation stages.

---

## 3. Problem Statement

Develop a mini compiler in C language that:

- Reads source code from input files
- Identifies tokens using lexical analysis
- Validates syntax using formal grammar rules
- Performs semantic checks on identifier usage
- Generates intermediate code (three-address code)
- Displays compilation statistics

### Supported Language Features

The compiler handles a minimal language with:

```
variable = expression
```

Where expressions can include:
- Identifiers (variable names): a, b, x, total
- Numbers: 10, 5, 100
- Operators: +, -, *, /
- Parentheses for grouping

### Example

**Input:**
```c
a = b + c * d
```

**Output:**
```
t1 = c * d
t2 = b + t1
a = t2
```

---

## 4. System Requirements

### Hardware

- Any standard laptop or desktop computer
- Minimum 1GB RAM
- 10MB free disk space

### Software

**Operating System:**
- Ubuntu Linux (recommended)
- Windows with WSL or MinGW
- macOS

**Development Tools:**
- GCC Compiler(version 5.0 or higher)
- Text editor (VS Code, Vim, Nano, etc.)
- Terminal/Command Prompt

**Installation Commands:**
```bash
# Ubuntu/Debian
sudo apt-get install gcc

# Fedora
sudo dnf install gcc

# macOS
xcode-select --install
```

**Compilation Command:**
```bash
gcc -o compiler main.c lexer.c parser.c codegen.c semantic_analyzer.c -Wall -Wextra
./compiler
```

---

## 5. Language Grammar

The compiler uses the following context-free grammar:

### Grammar Rules

```
Statement → id = Expression
Expression → Expression + Term | Expression - Term | Term
Term → Term * Factor | Term / Factor | Factor
Factor → id | number
```

### Operator Precedence

1. **Highest:** * and /(left to right)
2. **Lowest:** + and - (left to right)

### Examples

**Valid Statements:**
```
a = b + c * d
x = y * z + k
result = a + b - c / d
value = 10 + x * 5
```

**Invalid Statements:**
```
a = + b        # Operator at start
a = b c        # Missing operator
= b + c        # No variable name
a =            # No expression
```

---

## 6. Compiler Architecture

The mini compiler consists of **five main modules**:

### 6.1 Lexical Analyzer(lexer.c)

**Purpose:** Convert source code into tokens

**Functions:**
- Read characters from source file
- Skip whitespace and comments
- Identify and categorize tokens
- Build initial symbol table

**Token Types:**
| Type | Description | Examples |
|------|-------------|----------|
| Identifier | Variable names | a, x, total, count |
| Number | Numeric constants | 10, 5, 100 |
| Operator | Arithmetic symbols | +, -, *, / |
| Assignment | Equals sign | = |

**Example:**
```
Input: a = b + c

Output Tokens:
  IDENTIFIER(a)
  ASSIGNMENT
  IDENTIFIER(b)
  OPERATOR(+)
  IDENTIFIER(c)
```

### 6.2 Syntax Analyzer(parser.c)

**Purpose:** Validate token sequence against grammar rules

**Functions:**
- Parse tokens according to grammar
- Detect syntax errors
- Support multiple statements
- Handle operator precedence

**Validation Process:**
1. Check statement structure: `id = Expression`
2. Validate expression components
3. Verify operator placement
4. Ensure proper termination

**Example:**
```
Valid:   a = b + c
Invalid: a = + b     (Error: expected operand)
Invalid: a = b c     (Error: missing operator)
```

### 6.3 Symbol Table Module

**Purpose:** Store and manage identifiers

**Features:**
- Tracks all variable names
- Records declaration context
- Supports semantic analysis
- Generates formatted output

**Information Stored:**
- Variable name
- Line number
- Declaration status

### 6.4 Semantic Analyzer (semantic_analyzer.c)

**Purpose:** Ensure meaningful use of identifiers

**Functions:**
- Check if variables are defined before use
- Validate identifier references
- Track semantic errors
- Report undefined variables

**Example:**
```
If 'x' is used but never declared:
Semantic Error: Undefined identifier 'x'
```

### 6.5 Intermediate Code Generator (codegen.c)

**Purpose:** Generate three-address code

**Features:**
- Creates temporary variables (t1, t2, t3...)
- Respects operator precedence
- Produces linear instruction sequence
- Optimizes evaluation order

**Example:**
```
Input: a = b + c * d

Generated Code:
  t1 = c * d      (Evaluate multiplication first)
  t2 = b + t1     (Then addition)
 a = t2          (Final assignment)
```

---

## 7. System Flow

```
Source Code Input
       ↓
┌──────────────────────┐
│  LEXICAL ANALYSIS    │
│  - Tokenize input    │
│  - Build symbol table│
└──────────────────────┘
       ↓
  Token Stream
       ↓
┌──────────────────────┐
│   SYNTAX ANALYSIS    │
│  - Validate grammar  │
│  - Check structure   │
└──────────────────────┘
       ↓
  Syntax Valid?
       ↓
     Yes / \ No
       ↓   └──→ COMPILATION FAILED
       ↓
┌──────────────────────┐
│  SEMANTIC ANALYSIS   │
│  - Check identifiers │
│  - Validate usage    │
└──────────────────────┘
       ↓
  Semantics Valid?
       ↓
     Yes / \ No
       ↓   └──→ COMPILATION FAILED
       ↓
┌──────────────────────┐
│ INTERMEDIATE CODE    │
│  - Generate 3AC      │
│  - Create temp vars  │
└──────────────────────┘
       ↓
┌──────────────────────┐
│  COMPILATION         │
│     SUCCESSFUL       │
│  - Show statistics   │
└──────────────────────┘
```

---

## 8. Example Input Program

**File: input.txt**
```
// Mini Compiler Test Program
// This demonstrates multiple statements and comments

a = b + c * d
x = y * z + k
result = a + x -5
```

---

## 9. Expected Output

### Complete Compilation Output

```
=====================================
      MINI COMPILER STARTED
=====================================

Initializing compiler phases...

----- SOURCE PROGRAM -----
// Mini Compiler Test Program
// This demonstrates multiple statements and comments

a = b + c * d
x = y * z + k
result = a + x - 5

----- LEXICAL ANALYSIS -----
Tokens:
IDENTIFIER(a)
ASSIGNMENT
IDENTIFIER(b)
OPERATOR(+)
IDENTIFIER(c)
OPERATOR(*)
IDENTIFIER(d)
IDENTIFIER(x)
ASSIGNMENT
IDENTIFIER(y)
OPERATOR(*)
IDENTIFIER(z)
OPERATOR(+)
IDENTIFIER(k)
IDENTIFIER(result)
ASSIGNMENT
IDENTIFIER(a)
OPERATOR(+)
IDENTIFIER(x)
OPERATOR(-)
NUMBER(5)

----- SYMBOL TABLE -----
Name                 Line       Status
----                 ----       ------
a                   1          Declared
b                    1          Declared
c                    1          Declared
d                    1          Declared
x                    1          Declared
y                    1          Declared
z                    1          Declared
k                   1          Declared
result              1          Declared

----- SYNTAX ANALYSIS -----
Syntax is valid

----- SEMANTIC ANALYSIS -----
Semantic Analysis: All identifiers are properly defined

----- INTERMEDIATE CODE -----
Intermediate Code:
t1 = c * d
t2 = b + t1
a = t2
t3 = y * z
t4 = t3 + k
x = t4
t5 = a + x
t6 = t5 -5
result = t6

=====================================
      COMPILATION SUCCESSFUL
=====================================

----- COMPILATION STATISTICS -----
Total tokens processed:     22
Identifiers in symbol table: 9
Temporary variables used:    6
Intermediate code lines:     9
```

---

## 10. Project Structure

```
mini-compiler/
│
├── README.md              # User documentation
├── PDR.md                # This design document
├── PRESENTATION.md       # Presentation guide
│
├── compiler.h            # Header file with definitions
├── lexer.c               # Lexical analyzer
├── parser.c              # Syntax analyzer
├── semantic_analyzer.c   # Semantic analyzer
├── codegen.c             # Code generator
├── main.c                # Main program
│
├── input.txt            # Sample input (valid)
├── invalid.txt          # Sample input (invalid)
├── test_simple.txt      # Simple test case
├── test_complex.txt     # Complex test case
│
└── compiler             # Compiled executable (after build)
```

### File Descriptions

| File | Purpose |
|------|---------|
| **compiler.h** | Data structures, constants, function declarations |
| **lexer.c** | Tokenization, comment handling, symbol table building |
| **parser.c** | Grammar validation, syntax tree construction |
| **semantic_analyzer.c** | Identifier validation, semantic checks |
| **codegen.c** | Three-address code generation |
| **main.c** | Program orchestration, I/O handling |
| **input.txt** | Default test input with multiple statements |
| **invalid.txt** | Error case demonstration |

---

## 11. Testing Strategy

### Test Case Categories

#### Test 1: Simple Expression
**Input:** `a = b + c`
**Expected:** 2 intermediate code lines, 1 temporary variable

#### Test 2: Operator Precedence
**Input:** `x = y * z + k`
**Expected:** Multiplication evaluated before addition

#### Test3: Complex Expressions
**Input:** `a = b + c * d -e / f`
**Expected:** Correct precedence: * and / before + and -

#### Test4: Multiple Statements
**Input:** 
```
a = b + c
x = y * z
```
**Expected:** Both statements compiled sequentially

#### Test 5: With Comments
**Input:**
```
// Comment line
a = b + c // Inline comment
```
**Expected:** Comments ignored during processing

#### Test 6: Syntax Errors
**Input:** `a = + b c`
**Expected:** SYNTAX ERROR message, compilation halt

#### Test 7: Numbers in Expressions
**Input:** `x = 10 + y * 5`
**Expected:** Numbers handled correctly alongside identifiers

### Validation Checklist

- [ ] Lexical analysis identifies all token types
- [ ] Symbol table stores all identifiers
- [ ] Syntax analysis detects errors
- [ ] Semantic analysis validates usage
- [ ] Intermediate code respects precedence
- [ ] Statistics display accurate counts
- [ ] Error messages are clear and helpful
- [ ] Comments are properly ignored

---

## 12. Conclusion

This mini compiler project successfully demonstrates the fundamental phases of compilation:

### Key Achievements

✅ **Complete Implementation** - All major compiler phases implemented
✅ **Educational Value** - Clear, well-commented code for learning
✅ **Modular Design** - Separate modules for each phase
✅ **Error Handling** - Robust detection and reporting of errors
✅ **Real-world Concepts** - Demonstrates actual compiler techniques

### Learning Outcomes

Students will understand:

1. **How compilers work** - Step-by-step transformation process
2. **Lexical analysis** - Pattern matching and tokenization
3. **Parsing** - Grammar validation and structure checking
4. **Semantic analysis** - Meaning and context validation
5. **Code generation** - Intermediate representation creation

### Applications

This project serves as:
- Educational tool for compiler courses
- Foundation for more complex language processors
- Template for custom scripting languages
- Demonstration of system software concepts

---

**Document Version:** 2.0  
**Last Updated:** March 2026  
**Author:** Mini Compiler Development Team