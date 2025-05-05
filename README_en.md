<!-- English | [日本](./README.md) | [French](./README_fr.md)-->

<p align="center">
  <picture>
    <img height="300" alt="minishellImage" src="https://github.com/user-attachments/assets/96aab2ee-f9e3-4db8-ac33-61ad4aed5ad8">
  </picture>
</p>

<p align="center">
Minishell is a lightweight shell implemented in C, based on core features found in Bash, such as command execution, redirection, piping, and environment variable expansion.<br>
It handles a wide range of low-level OS mechanisms, including process creation and management, input/output control via file descriptors, and signal handling,<br>
with careful attention to closely mimic the behavior of Bash wherever possible.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/-C-213a70.svg?logo=C&style=flat">
  <img src="https://img.shields.io/badge/-Linux-ea5520.svg?logo=linux&style=flat">
</p>

<hr>

| Feature Category     | Description |
|----------------------|-------------|
| Prompt               | Always displays the `minish$` prompt with support for input history via `readline`          |
| Command Execution    | Executes commands found in the `PATH` or binaries specified via relative/absolute paths using `execve(2)` |
| Redirection          | Correctly handles `<`, `>`, `>>`, and `<<` (here-document), including nested redirections    |
| Pipes                | Recursively expands and executes pipelines of unlimited length                               |
| Environment Expansion| Expands `$VAR` and the exit status `$?` token by token                                       |
| Built-in Commands    | Supports `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`                           |
| Signal Handling      | Handles `Ctrl-C`, `Ctrl-\`, and `Ctrl-D`                                                     |
| Error Compatibility  | Returns the same exit codes as Bash for command not found (127), permission denied (126), and syntax errors (2) |


## Make Command List
| Make Target | Description                                                                                     |
|-------------|-------------------------------------------------------------------------------------------------|
| all         | Compiles the dependent source files and creates the executable. Usually includes the $(NAME) target. |
| clean       | Removes object files (*.o, etc.) generated during compilation.                                  |
| fclean      | Performs `clean` and additionally removes the generated executable and any libraries.           |
| re          | Runs `fclean` followed by `all` to rebuild the project from scratch.                            |



## How to Build
```
$ git clone <this repository>
$ cd minishell
$ make
$ ./minishell
minish$
```
## Directory Structure
```
builtin/     … Implementation of built-in commands  
execute/     … Fork/exec logic and pipeline management  
expand/      … Variable, parameter, and quote expansion  
misc/        … Signal handling, error handling, and environment utilities  
parse/       … Recursive descent parser  
redirect/    … Redirection and here-document handling  
tokenize/    … Lexer (tokenizer)  
pipeline/    … Pipeline node creation and execution  
tester.sh    … Bash compatibility test script  
```

## Norminetteへの適応 ※2025年05月時点

## Compliance with Norminette (as of May 2025)

This project strictly follows the 42 School Norminette rules (version 3.3.58).  
[Norminette](https://github.com/42School/norminette) is a tool designed to enforce consistent coding style across C projects at 42.  
Key rules include:

- Maximum of 25 lines per function  
- Maximum of 80 characters per line  
- Maximum of 5 functions per file  
- Required function headers in a specific format  
- Restrictions on the use of standard library functions  
- Strict rules for variable declaration and naming conventions  
- Indentation must be done using tabs  
- Forbidden use of `for`, `switch`, `do-while`, and similar statements  

  
## Testing
After compilation, you can run `tester.sh` to automatically compare the output and exit codes between Bash and Minishell.  
This allows you to verify at once whether the main features are compatible.
<p align="left">
  <img src="https://github.com/user-attachments/assets/acb01f2c-5a10-4465-86d0-332571e75438" height="500">
</p>

## Evaluation

Date of Evaluation: YYYY-MM-DD

Mandatory Part: XX / 100

Bonus: XX / 15
