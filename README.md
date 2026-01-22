*This project has been created as part of the 42 curriculum by <sarayapa>.*

# pipex

## Description
**pipex** is a project from the 42 curriculum designed to deepen the understanding of **Unix pipes** and **process management**.

The objective of this project is to reproduce the behavior of the following shell command:

```bash
< infile cmd1 | cmd2 > outfile
```
## Instructions
Through this project, we learn and practice:
- Creating processes using fork()
- Connecting processes with pipe()
- Redirecting file descriptors using dup2()
- Executing commands with execve()
- Proper error handling and memory management
### Requirements
Operating System: Linux / macOS

Compiler: cc

Make: GNU Make

### Compilation
Compile the project using:
```bash
make
```
Remove object files:
```bash
make clean
```
Remove all compiled files:
```bash
make fclean
```
Recompile everything:
```bash
make re
```
### Execution

Program usage:
```bash
./pipex infile "cmd1" "cmd2" outfile
```
Example:
```bash
./pipex infile "ls -l" "wc -l" outfile
```

This behaves exactly like:
```bash
< infile ls -l | wc -l > outfile
```
## Resources
### Documentation & References.

Linux manual pages :
```bash
man pipe
```
```bash
man fork
```
```bash
man dup2
```
```bash
man waitpid
```
```bash
man ACCESS
```
```bash
man perror
```

### AI Usage Disclosure
AI tools were used **solely as learning assistance**, specifically for:
- Clarifying UNIX system calls behavior (e.g. pipe, fork, execve)
- Explaining error causes and debugging strategies
