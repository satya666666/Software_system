/*
============================================================================
Name : 8g.c
Author : Satyam Gupta
Description : Write a separate program using signal system call to catch the following signals.
g. SIGPROF (use setitimer system call)
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void sigprof_handler(int signum)    // Signal handler function for SIGPROF
{
    printf("Caught signal %d (SIGPROF): Profiling timer expired.\n", signum);
    exit(0);  
}
int main() {
    struct sigaction sa;
    struct itimerval timer;

    // Set up the signal handler for SIGPROF
    sa.sa_handler = sigprof_handler;
    sa.sa_flags = 0;                                          // No special flags
    sigemptyset(&sa.sa_mask);                                 // No additional signals to block while handling
    if (sigaction(SIGPROF, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    timer.it_value.tv_sec = 5;      
    timer.it_value.tv_usec = 0;     
    timer.it_interval.tv_sec = 5;    
    timer.it_interval.tv_usec = 0;   

    // Set the profiling timer (counts both user and system CPU time)
    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) 
    {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }
    while (1) {
      
        for (volatile int i = 0; i < 100000000; i++);
        getppid();                                       // System call to consume system mode CPU time
    }

    return 0;
}



// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 8g.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Caught signal 27 (SIGPROF): Profiling timer expired.
