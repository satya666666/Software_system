/*
============================================================================
Name : 8e.c
Author : Satyam Gupta
Description : Write a separate program using signal system call to catch the following signals.
e. SIGALRM (use setitimer system call)
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void sigalrm_handler(int signum)               // Signal handler function for SIGALRM
{
    printf("Caught signal %d (SIGALRM): Timer expired.\n", signum);
    exit(0);  
}
int main() {
    struct sigaction sa;
    struct itimerval timer;

    // Set up the signal handler for SIGALRM
    sa.sa_handler = sigalrm_handler;
    sa.sa_flags = 0;                         // No special flags
    sigemptyset(&sa.sa_mask);                // No additional signals to block while handling
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    timer.it_value.tv_sec = 5;       // Configure the timer to expire after 5 seconds and then every 5 seconds
    timer.it_value.tv_usec = 0;     
    timer.it_interval.tv_sec = 5;    
    timer.it_interval.tv_usec = 0;   
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }
    while (1) {
        pause();  
    }

    return 0;
}



// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 8e.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Caught signal 14 (SIGALRM): Timer expired.