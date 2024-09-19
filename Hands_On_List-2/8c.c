/*
============================================================================
Name : 8c.c
Author : Satyam Gupta
Description : Write a separate program using signal system call to catch the following signals :
c. SIGFPE
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void sigfpe_handler(int signum) {
    printf("Caught SIGFPE: Floating-point exception occurred !!\n");
    exit(1); 
}
int main() {
    if (signal(SIGFPE, sigfpe_handler) == SIG_ERR)            // Register the signal handler for SIGFPE
     {
        printf("Error setting up signal handler.\n");
        return 1;
    }
    
    int x = 1;
    int y = 0;
    int result = x / y;                        // divide by zero causes SIGFPE
    printf("Result: %d\n", result);            // line will never reached
    return 0;
}

// Output:


// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 8c.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Caught SIGFPE: Floating-point exception occurred !!