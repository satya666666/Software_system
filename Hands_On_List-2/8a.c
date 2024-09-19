/*
============================================================================
Name : 8a.c
Author : Satyam Gupta
Description : Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigsegv_handler(int signum)   // function for print the message of SIGSEGV
{
printf("Caught signal %d (SIGSEGV): Segmentation Fault occurred.\n", signum);
exit(1);  
}
int main() {
signal(SIGSEGV, sigsegv_handler);          // Register the signal handler for SIGSEGV

    // Intentionally cause a segmentation fault to demonstrate the handler
    int *ptr = NULL;  // Create a NULL pointer
    *ptr = 42;        // Dereference the NULL pointer, which causes a SIGSEGV
    printf("This line will not be executed due to the segmentation fault.\n");
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 8a.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Caught signal 11 (SIGSEGV): Segmentation Fault occurred.
