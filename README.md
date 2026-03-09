# Mini Compiler Project

A simple compiler implementation in C that demonstrates the fundamental phases of compilation. This project is perfect for students learning about compiler design or anyone interested in understanding how compilers work.

## Project Overview

### What is a Compiler?

A **compiler** is a special program that translates code written in one programming language (source code) into another language (usually machine code). Think of it as a translator that converts human-readable code into computer-readable instructions.

### What Does This Mini Compiler Do?

This mini compiler processes simple assignment expressions like:
```
a = b + c * d
```

It doesn't create executable programs, but it demonstrates all the important steps that real compilers use:
1. **Reading** the source code
2. **Breaking it down** into meaningful pieces (tokens)
3. **Checking** if the code follows grammar rules
4. **Validating** that all variables are properly used
5. **Generating** intermediate code (three-address code)

For example, `a = b + c * d` becomes:
```
t1 = c * d
t2 = b + t1
a = t2
```

## Features

This mini compiler implements the following phases:

### 1. Source Program Reading
- Reads input from text files
- Supports multiple statements
- Ignores comments(lines starting with `//`)

### 2. Lexical Analysis
- Breaks source code into tokens
- Identifies:
  - **Identifiers**: variable names (a, b, total, x)
  - **Numbers**: numeric constants (10, 5, 100)
  - **Operators**: arithmetic symbols (+, -, *, /)
  - **Assignment**: equals sign (=)

### 3. Symbol Table
- Stores all variable names discovered during analysis
- Tracks which variables are declared/used
- Displays a formatted table of all identifiers

### 4. Syntax Analysis
- Checks if code follows grammar rules
- Validates expression structure
- Reports syntax errors with helpful messages
- Stops compilation if errors are found

### 5. Semantic Analysis
- Verifies all variables are properly defined
- Checks for meaningful usage of identifiers
- Ensures logical correctness

### 6. Intermediate Code Generation
- Produces three-address code
- Uses temporary variables (t1, t2, t3...)
- Respects operator precedence (* and / before + and -)

### 7. Compilation Statistics
- Shows total tokens processed
- Displays number of identifiers
- Counts temporary variables used
- Reports intermediate code lines generated

## Project Structure

The project consists of these files:

### Core Source Files

**compiler.h**
- Header file containing definitions and declarations
- Defines token types and data structures
- Declares functions used across modules

**lexer.c**
- Implements the Lexical Analyzer
- Converts source code to tokens
- Builds the symbol table
- Handles comments

**parser.c**
- Implements the Syntax Analyzer
- Validates grammar rules
- Checks expression structure
- Supports multiple statements

**semantic_analyzer.c**
- Implements the Semantic Analyzer
- Validates identifier usage
- Checks symbol table references
- Ensures semantic correctness

**codegen.c**
- Implements the Intermediate Code Generator
- Produces three-address code
- Manages temporary variables
- Generates final output

**main.c**
- Main entry point of the compiler
- Orchestrates all compiler phases
- Handles user input/output
- Displays compilation statistics

### Input Files

**input.txt**
- Default input file
- Contains sample programs
- Used when no filename is specified

**invalid.txt**
- Contains intentionally incorrect code
- Used to test error handling
- Demonstrates syntax error detection

## How to Clone the Repository

If you're new to GitHub, follow these simple steps:

### Step 1: Install Git
First, make sure Git is installed on your computer:
- **Windows**: Download from [git-scm.com](https://git-scm.com)
- **Linux**: Run `sudo apt-get install git`
- **Mac**: Run `brew install git`

### Step 2: Open Terminal or Command Prompt
- **Windows**: Press Win + R, type "cmd", press Enter
- **Linux/Mac**: Open Terminal application

### Step 3: Navigate to Your Projects Folder
```bash
cd Documents
```
(Or any folder where you want to store the project)

### Step 4: Clone the Repository
Copy the repository URL from GitHub, then run:
```bash
git clone https://github.com/roonakyadav/mini-compiler.git
```

### Step 5: Enter the Project Directory
```bash
cd mini-compiler
```

That's it! You now have the project on your computer.

## How to Compile the Program

To convert the C source code into an executable program, use the GCC compiler.

### Compilation Command

```bash
gcc -o compiler main.c lexer.c parser.c codegen.c semantic_analyzer.c -Wall -Wextra
```

### What This Command Means:

- **gcc**: The GNU Compiler Collection command
- **-o compiler**: Output filename will be "compiler"
- **main.c lexer.c parser.c codegen.c semantic_analyzer.c**: All source files to compile
- **-Wall -Wextra**: Show all warnings (helps catch potential issues)

### If Compilation Succeeds:
You'll see a command prompt with no error messages, and a new file called `compiler` will appear.

### If Compilation Fails:
Check that:
- All `.c` files exist in the current directory
- GCC is installed (`gcc --version`)
- You have permission to create files

## How to Run the Compiler

### Method 1: Using Default Input File

```bash
./compiler
```

This runs the compiler using `input.txt` as the default input file.

### Method 2: Specifying a Custom Input File

```bash
./compiler filename.txt
```

Replace `filename.txt` with your input file name.

Examples:
```bash
./compiler input.txt
./compiler invalid.txt
./compiler myprogram.txt
```

### Expected Behavior:

**Successful compilation:**
- Shows all compiler phases
- Displays "COMPILATION SUCCESSFUL"
- Shows compilation statistics

**Failed compilation:**
- Stops at the error phase
- Shows "COMPILATION FAILED"
- No statistics displayed

## Example Output

When you run the compiler, you'll see output organized in sections:

### 1. SOURCE PROGRAM
Shows your input code exactly as written.

### 2. LEXICAL ANALYSIS
Lists all tokens found:
```
IDENTIFIER(a)
ASSIGNMENT
IDENTIFIER(b)
OPERATOR(+)
IDENTIFIER(c)
OPERATOR(*)
IDENTIFIER(d)
```

### 3. SYMBOL TABLE
Displays all variables:
```
Name                 Line       Status
----                 ----       ------
a                   1          Declared
b                   1          Declared
c                   1          Declared
d                   1          Declared
```

### 4. SYNTAX ANALYSIS
Shows if code structure is valid:
```
Syntax is valid
```
or
```
SYNTAX ERROR
```

### 5. SEMANTIC ANALYSIS
Confirms proper variable usage:
```
Semantic Analysis: All identifiers are properly defined
```

### 6. INTERMEDIATE CODE
Generated three-address code:
```
t1 = c * d
t2 = b + t1
a = t2
```

### 7. COMPILATION STATISTICS
Summary of the compilation:
```
Total tokens processed:      8
Identifiers in symbol table: 4
Temporary variables used:    2
Intermediate code lines:     3
```

## How to Demonstrate the Project

For a presentation or viva, follow this sequence:

### 1. Show Successful Compilation
```bash
./compiler input.txt
```
Explain each phase as it appears.

### 2. Show Error Handling
```bash
./compiler invalid.txt
```
Demonstrate how the compiler detects and reports errors.

### 3. Show Custom Input
Create a simple file:
```bash
echo "x = y + z * 2" > test.txt
./compiler test.txt
```

### 4. Highlight Key Features
- Point out comment handling in input.txt
- Show multiple statements support
- Explain the statistics section

### 5. Answer Questions
Refer to the PRESENTATION.md file for common questions.

## Common Errors

### Error 1: gcc not installed

**Message:** `command not found: gcc`

**Solution:**
```bash
# Ubuntu/Debian
sudo apt-get install gcc

# Fedora
sudo dnf install gcc

# Windows
Install MinGW or use WSL

# Mac
xcode-select --install
```

### Error 2: Permission denied

**Message:** `Permission denied`

**Solution:**
```bash
chmod +x compiler
./compiler
```

### Error 3: File not found

**Message:** `Cannot open input file 'filename.txt'`

**Solution:**
- Check you're in the correct directory: `ls`
- Verify the file exists: `ls filename.txt`
- Use full path if needed: `./compiler/path/to/file.txt`

### Error 4: Compilation warnings

**Message:** Various warnings during compilation

**Solution:**
- Warnings don't prevent compilation
- They indicate potential issues
- Check the specific warning message
- Most warnings in this project are safe to ignore

### Error 5: Segmentation fault

**Message:** `Segmentation fault (core dumped)`

**Solution:**
- Check input file format
- Ensure proper statement syntax: `variable = expression`
- Don't use empty files
- Verify all source files are present

---

**Need Help?**
- Check that all `.c` and `.h` files are in the directory
- Make sure you have GCC version 5.0 or higher
- Read error messages carefully - they usually tell you what's wrong

---

## How to Make This Your Own Project

Want to submit this compiler as your own project? Follow these simple steps!

### Step 1: Clone the Repository

First, get the project on your computer:

```bash
git clone https://github.com/yourusername/mini-compiler.git
cd mini-compiler
```

**What this does:**
- `git clone` - Downloads the entire project
- `cd mini-compiler` - Enters the project folder

---

### Step 2: Change the Author Name

Make this project yours by updating the author name.

#### In README.md:
Open `README.md` in a text editor and find this line (near the bottom):

```
**Author:** Mini Compiler Development Team
```

Change it to:

```
**Author:** Your Name Here
```

#### In PDR.md:
Open `PDR.md` and scroll to the very bottom. Find:

```
**Author:** Mini Compiler Development Team
```

Change it to:

```
**Author:** Your Name Here
```

**Tip:** Use any text editor (VS Code, Notepad++, Nano, Vim) to make these changes.

---

### Step 3: Compile the Project

Convert the C source code into an executable program:

```bash
gcc -o compiler main.c lexer.c parser.c codegen.c semantic_analyzer.c -Wall -Wextra
```

**What this command means:**
- `gcc` - The C compiler
- `-o compiler` - Name the output file"compiler"
- List of `.c` files - All source code files to compile
- `-Wall -Wextra` - Show helpful warnings

**If successful:** You'll see no error messages, and a new file called `compiler` will appear.

---

### Step 4: Run the Compiler

Test that everything works:

```bash
./compiler
```

This runs the compiler using the default input file (`input.txt`).

You should see all the compiler phases displayed on your screen!

**Try it with other files:**

```bash
./compiler invalid.txt   # See error handling
./compiler test_simple.txt # Simple example
```

---

### Step 5: Take Screenshots for Your Lab Report

Capture these important moments:

#### Screenshot 1: Successful Compilation
Show the compilation command working:
```
gcc -o compiler main.c lexer.c parser.c codegen.c semantic_analyzer.c -Wall -Wextra
```
Take a screenshot showing **no error messages**.

#### Screenshot 2: Successful Program Run
Run `./compiler` and capture the complete output showing:
- SOURCE PROGRAM section
- LEXICAL ANALYSIS section
- SYMBOL TABLE section
- SYNTAX ANALYSIS section
- SEMANTIC ANALYSIS section
- INTERMEDIATE CODE section
- COMPILATION SUCCESSFUL message
- COMPILATION STATISTICS

#### Screenshot 3: Syntax Error Example
Run `./compiler invalid.txt` and capture:
- The syntax error message
- "SYNTAX ERROR" output
- "=== COMPILATION FAILED ===" message

**Pro tip:** On Windows, use `Win + Shift + S`. On Mac, use `Cmd + Shift + 4`. On Linux, use `Print Screen` or your distribution's screenshot tool.

---

### Step 6: Push to Your Own GitHub Repository

Share your project with the world!

#### Part A: Create a New Repository on GitHub

1. Go to [github.com](https://github.com)
2. Click the **"+"** icon (top right)
3. Select **"New repository"**
4. Name it: `mini-compiler`
5. Choose **Public** or **Private**
6. **Don't** check "Initialize this repository with a README"
7. Click **"Create repository"**
8. Copy the repository URL (looks like: `https://github.com/yourusername/mini-compiler.git`)

#### Part B: Upload Your Code

Open terminal/command prompt in your project folder and run these commands **one by one**:

```bash
# Initialize Git in your project folder
git init

# Add all files to Git
git add .

# Save your first commit
git commit -m "Mini compiler project"

# Rename your branch to 'main'
git branch -M main

# Connect to your GitHub repository
git remote add origin https://github.com/yourusername/mini-compiler.git

# Upload your code
git push -u origin main
```

**What each command does:**
- `git init` - Starts tracking your project with Git
- `git add .` - Prepares all files for upload
- `git commit` - Saves a snapshot of your work
- `git branch -M main` - Names your main branch
- `git remote add origin` - Links to your GitHub repository
- `git push` - Uploads your code to GitHub

**Done!** Your project is now on GitHub. Share the link with your friends and teachers!

---

## How to Present This Project to Your Teacher

Nervous about presenting? Here's exactly what to do:

### Before the Presentation

1. **Practice running the compiler:**
   ```bash
   ./compiler input.txt
   ```

2. **Know what each phase does:**
   - **Lexical Analysis:** Breaks code into tokens (like words in a sentence)
   - **Symbol Table:** Stores all variable names
   - **Syntax Analysis:** Checks if code follows grammar rules
   - **Semantic Analysis:** Ensures variables are used correctly
   - **Intermediate Code:** Generates step-by-step instructions

3. **Prepare two examples:**
   - One that works: `./compiler input.txt`
   - One that fails: `./compiler invalid.txt`

---

### During the Presentation

#### Step 1: Start the Demo

Say: *"Let me show you how the mini compiler works."*

Run:
```bash
./compiler input.txt
```

#### Step 2: Explain Each Phase as It Appears

Point to the screen and explain:

**"This is Lexical Analysis - it breaks the code into meaningful pieces called tokens, just like identifying words and punctuation in a sentence."**

**"The Symbol Table stores all the variable names we're using - think of it as a dictionary for our program."**

**"Syntax Analysis checks if our code follows the grammar rules - like checking if a sentence is structured correctly."**

**"Semantic Analysis makes sure we're using variables properly - no undefined variables allowed!"**

**"Finally, Intermediate Code Generation creates simple, step-by-step instructions. For example, `a = b + c * d` becomes:**
```
t1 = c * d
t2 = b + t1
a = t2
```
**This respects operator precedence - multiplication happens before addition."**

#### Step 3: Show Error Handling

Say: *"Now let me show you what happens when there's an error."*

Run:
```bash
./compiler invalid.txt
```

Explain: *"The compiler detects the syntax error immediately, shows a clear error message, and stops compilation. This prevents generating incorrect code."*

#### Step 4: Highlight Key Features

Mention:
- ✅ Handles multiple statements in one file
- ✅ Ignores comments(lines starting with `//`)
- ✅ Supports numbers and variables together
- ✅ Shows compilation statistics
- ✅ Clear, helpful error messages

---

### Common Questions Your Teacher Might Ask

**Q: "What did you learn from this project?"**

A: *"I learned how compilers translate high-level code into machine instructions. I now understand lexical analysis, parsing, semantic checking, and code generation - the same phases that real compilers like GCC use!"*

**Q: "How does it handle operator precedence?"**

A: *"The grammar ensures multiplication and division are evaluated before addition and subtraction. So `a = b + c * d` correctly calculates `c * d` first, then adds `b`."*

**Q: "What happens if there's an error?"**

A: *"The compiler stops immediately at the first error, shows a clear message explaining what went wrong, and exits without generating code. This is called 'fail-fast' design."*

**Q: "Can this be extended?"**

A: *"Absolutely! We could add support for parentheses, more operators, if-statements, loops, or even functions. The modular design makes it easy to extend each phase."*

---

### Final Tips for Success

✅ **Practice beforehand** - Run through the demo 3-4 times before presenting

✅ **Speak slowly** - Don't rush through the phases

✅ **Point to the screen** - Help your teacher follow along

✅ **Be confident** - You built a compiler! That's impressive!

✅ **Have backups** - Keep screenshots ready in case live demo fails

❌ **Don't apologize** - If something goes wrong, just say "Let me try that again"

---

**Remember:** Your teacher wants you to succeed. They're not trying to trick you - they want to see that you understand the concepts. Be honest, be prepared, and be proud of what you've built!

**Good luck! 🎓**
