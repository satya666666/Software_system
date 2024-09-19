/*
============================================================================
Name : 10b.c
Author : Satyam Gupta
Description : Write a separate program using sigaction system call to catch the following signals.
b. SIGINT
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void sigint_handler(int signum)                          // Signal handler function for SIGINT
{
    printf("Caught signal %d (SIGINT): Interrupt from keyboard (Ctrl+C).\n", signum);
    exit(0);  
}
int main() {
    struct sigaction sa;

    // Set up the signal handler for SIGINT
    sa.sa_handler = sigint_handler;                         // Assign the handler function
    sa.sa_flags = 0;                                        // No special flags
    sigemptyset(&sa.sa_mask);                               // No additional signals will be blocked

    // Register the handler using sigaction
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    while (1) {
        printf("Program is running. Press Ctrl+C to trigger SIGINT...\n");
        sleep(1);
        
    }

    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 10b.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Program is running. Press Ctrl+C to trigger SIGINT...
// Program is running. Press Ctrl+C to trigger SIGINT...
// Program is running. Press Ctrl+C to trigger SIGINT...
// ^CCaught signal 2 (SIGINT): Interrupt from keyboard (Ctrl+C).