/*
============================================================================
Name : 8d.c
Author : Satyam Gupta
Description : Write a separate program using signal system call to catch the following signals.
d. SIGALRM (use alarm system call)
Date: 7th Sept. 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void sigalrm_handler(int signum) {
    printf("Caught SIGALRM: Alarm signal received!\n");
}
int main() {
    if (signal(SIGALRM, sigalrm_handler) == SIG_ERR)    // signal handler for SIGALRM
    {
        perror("Error setting up signal handler");
        return EXIT_FAILURE;
    }
    alarm(2);    // set alarm for 2 seconds
    while (1) {
        printf("Waiting for the alarm...\n");
        sleep(1);    // Sleep for one second before checking again
    }

    return EXIT_SUCCESS;   // line will never reached
}



// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 8d.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Waiting for the alarm...
// Waiting for the alarm...
// Caught SIGALRM: Alarm signal received!
// Waiting for the alarm...
// Waiting for the alarm...
// ^C