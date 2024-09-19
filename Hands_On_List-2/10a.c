/*
============================================================================
Name : 10a.c
Author : Satyam Gupta
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigsegv_handler(int signum)               // Signal handler function for SIGSEGV
{
    printf("Caught signal %d (SIGSEGV): Segmentation fault occurred.\n", signum);
    exit(1); 
}
int main() {
    struct sigaction sa;

    // Set up the signal handler for SIGSEGV
    sa.sa_handler = sigsegv_handler;
    sa.sa_flags = 0;                                 // No special flags
    sigemptyset(&sa.sa_mask);                        // No additional signals to block while handling
    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    int *ptr = NULL;
    *ptr = 42;                                                // Deferencing NULL pointer cause a segmentation fault (SIGSEGV)
    
     printf("This line will not be executed.\n");            // line will not executed due to the segmentation fault
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 10a.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Caught signal 11 (SIGSEGV): Segmentation fault occurred.