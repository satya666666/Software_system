/*
============================================================================
Name : 10c.c
Author : Satyam Gupta
Description : Write a separate program using sigaction system call to catch the following signals.
c. SIGFPE
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void sigfpe_handler(int signum)                         // Signal handler function for SIGFPE
{
    printf("Caught signal %d (SIGFPE): Floating-point exception occurred.\n", signum);
    exit(1);  
}
int main() {
    struct sigaction sa;
    // Set up the signal handler for SIGFPE
    sa.sa_handler = sigfpe_handler;                  // Assign the handler function
    sa.sa_flags = 0;                                 // No special flags
    sigemptyset(&sa.sa_mask);                          // No additional signals will be blocked during handling
    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    int x = 5;
    int y = 0;
    int z = x / y;  // This will cause division by zero, triggering SIGFPE
    printf("This line will not be executed.\n");                    // This line will not be executed due to the floating-point exception
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 10c.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Caught signal 8 (SIGFPE): Floating-point exception occurred.