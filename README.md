# Project name: pipex 

## Requirements:
- **Files to turn in:** Makefile, \*.c, \*.h
- **Makefile rules:** Name, all, clean, flclean, re
- **Arguments:** file1 cmd1 cmd2 file2
- **External functs:** open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpd, ft_printf
- **Libft auth:** Yes

## Description:
This project is about handling pipes. Your program will be executed as follows:

`./pipex file1 cmd1 cmd2 file2`
- `file1` and `file2` are **file names**
- `cmd1` and `cmd2` are **shell commands** with their parameters

And it must behave exactly the same as:

`$> < file1 cmd1 | cmd2 > file2`

## pipe
```
int pipefd[2];
if (pipe(pipefd) == -1) {
    // Error handling
}

// pipefd[0] is the read end, pipefd[1] is the write end
```

## fork
```
pid_t pid;

pid = fork();
if (pid == -1) {
    // Error handling
} else if (pid == 0) {
    // Child process
    // Execute command, redirect input/output as needed
} else {
    // Parent process
    // Possibly wait for child process to finish
}
```
## dup2
**Input redirection:**  
```
dup2(pipefd[1], STDOUT_FILENO);
```
**Output redirection:** 
```
dup2(pipefd[1], STDOUT_FILENO);
```
## access
```
if (access("file.txt", F_OK) == -1) {
    // File does not exist, handle error
}
```
*The F_OK flag is used to check for the existence of the file. 
You can also use other flags like R_OK, W_OK, and X_OK to check for read, write, and execute permissions, respectively.*
## execve
```
char *cmd[] = {"/bin/ls", "-l", NULL}; // Command to execute
char *envp[] = {NULL}; // Environment variables

if (fork() == 0) {
    // In child process
    execve(cmd[0], cmd, envp);
    // Error handling if execve returns
}
// Parent process continues here
```

## waitpd
```
pid_t pid;
int status;

pid = fork();
if (pid == -1) {
    // Error handling for fork
} else if (pid == 0) {
    // Child process code
} else {
    // Parent process waits for child to finish
    if (waitpid(pid, &status, 0) == -1) {
        // Error handling for waitpid
    }
    // Optionally use 'status' to determine how the child process terminated
}
```