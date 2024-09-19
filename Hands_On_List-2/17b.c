/*
============================================================================
Name : 17b.c
Author : Satyam Gupta
Description : Write a program to execute ls -l | wc.
b. use dup2
Date: 11th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    int pipefd[2];                      // Array to hold the pipe file descriptors
    pid_t pid1, pid2;
    if (pipe(pipefd) == -1)             // Create a pipe
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid1 = fork();                                 // First fork to execute 'ls -l'
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) {
        close(pipefd[0]);                                 // Child process 1: Executes 'ls -l' & Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);                   // Redirect stdout to the write end of the pipe
        close(pipefd[1]);                                 // Close the original write end file descriptor
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");                               // If execlp fails
        exit(EXIT_FAILURE);
    }
    pid2 = fork();                                          // Second fork to execute 'wc'
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0) {
        close(pipefd[1]);                           // Child process 2: Executes 'wc' & Close the write end of the pipe
        dup2(pipefd[0], STDIN_FILENO);               // Redirect stdin to the read end of the pipe
        close(pipefd[0]);                            // Close the original read end file descriptor

        execlp("wc", "wc", NULL);                     // Execute 'wc'
        perror("execlp wc");                          // If execlp fails
        exit(EXIT_FAILURE);
    }
    close(pipefd[0]);                                 // Parent process: Close both ends of the pipe
    close(pipefd[1]);

    wait(NULL);                                       // Wait for both child processes to finish
    wait(NULL);
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 17b.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
//      55     488    2787

