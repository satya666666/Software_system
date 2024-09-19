/*
============================================================================
Name : 23.c
Author : Satyam Gupta
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 14th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>

int main() {
    // 1. Maximum number of files that can be opened by a process
    struct rlimit limit;
    
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Maximum number of files that can be opened in a process: %lu\n", limit.rlim_cur);
    } else {
        perror("Error getting RLIMIT_NOFILE");
        exit(EXIT_FAILURE);
    }

    // 2. Size of a pipe (circular buffer)
    int pipefds[2];
    if (pipe(pipefds) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }

#ifdef F_GETPIPE_SZ
    // Check if F_GETPIPE_SZ is supported
    int pipe_size = fcntl(pipefds[0], F_GETPIPE_SZ);
    if (pipe_size != -1) {
        printf("Size of the pipe (circular buffer): %d bytes\n", pipe_size);
    } else {
        perror("Error getting pipe size");
        exit(EXIT_FAILURE);
    }
#else
    // Fallback if F_GETPIPE_SZ is not defined
    printf("F_GETPIPE_SZ is not supported on this system.\n");
#endif

    // Close pipe file descriptors
    close(pipefds[0]);
    close(pipefds[1]);

    return 0;
}



// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 23.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Maximum number of files that can be opened in a process: 1048576
// F_GETPIPE_SZ is not supported on this system.
