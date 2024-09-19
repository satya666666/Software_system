/*
============================================================================
Name : 1b.c
Author : Satyam Gupta
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second:  
b. ITIMER_VIRTUAL
Date: 6th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void timer_handler(int signum) {
    static int count = 0;
    printf("Virtual Timer expired %d times\n", ++count);
}

int main() {
    struct sigaction sa;
    struct itimerval timer;

    sa.sa_handler = &timer_handler;           // Setup the signal handler for SIGVTALRM
    sa.sa_flags = SA_RESTART;                 // Restart functions if interrupted by handler
    sigaction(SIGVTALRM, &sa, NULL);

    timer.it_value.tv_sec = 10;                // Configure the timer to expire after 10 seconds and 10 microseconds
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;               // After the initial expiration, the timer will reset to 10 seconds and 10 microseconds
    timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);        // Start the virtual timer

    while (1) {
        for (volatile int i = 0; i < 100000000; i++);  // Busy loop to simulate work
    }

    return 0;
}



// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 1b.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Virtual Timer expired 1 times
// Virtual Timer expired 2 times
// ^C