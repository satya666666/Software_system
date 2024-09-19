/*
============================================================================
Name : 8b.c
Author : Satyam Gupta
Description : Write a separate program using signal system call to catch the following signals.
b. SIGINT
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int signum)   // Signal handler function for SIGINT
{
printf("Caught signal %d (SIGINT): Interrupt signal received. Exiting gracefully...\n", signum);
exit(0);  
}
int main() {
    signal(SIGINT, sigint_handler);     // Register the signal handler for SIGINT
    while (1) {
        printf("Running... Press Ctrl+C to send SIGINT signal.\n");
        sleep(1);  
    }
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 8b.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Running... Press Ctrl+C to send SIGINT signal.
// Running... Press Ctrl+C to send SIGINT signal.
// Running... Press Ctrl+C to send SIGINT signal.
// Running... Press Ctrl+C to send SIGINT signal.
// Running... Press Ctrl+C to send SIGINT signal.
// ^CCaught signal 2 (SIGINT): Interrupt signal received. Exiting gracefully...