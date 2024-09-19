/*
============================================================================
Name : 1a.c
Author : Satyam Gupta
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second:  
a. ITIMER_REAL
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
printf("Timer expired %d times\n", ++count);
}
int main() {
struct sigaction sa;
struct itimerval timer;
sa.sa_handler = &timer_handler;      // Install the timer handler
sa.sa_flags = SA_RESTART;
sigaction(SIGALRM, &sa, NULL);           // Configure the timer to expire after 10 seconds
timer.it_value.tv_sec = 10;
timer.it_value.tv_usec = 10;

timer.it_interval.tv_sec = 10;             // And every 10 seconds and 10 microseconds after this
timer.it_interval.tv_usec = 10;
setitimer(ITIMER_REAL, &timer, NULL);       // Start the timer real
while (1) {
pause();
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 1a.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Timer expired 1 times
// Timer expired 2 times
// Timer expired 3 times
// ^C
