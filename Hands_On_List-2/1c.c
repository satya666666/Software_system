/*
============================================================================
Name : 1c.c
Author : Satyam Gupta
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second:  
c. ITIMER_PROF
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
printf("Profiling Timer expired %d times\n", ++count);
}
int main() {
struct sigaction sa;
struct itimerval timer;

sa.sa_handler = &timer_handler;                   // Install the timer handler
sa.sa_flags = SA_RESTART;
sigaction(SIGPROF, &sa, NULL);

timer.it_value.tv_sec = 10;                          // Configure the timer to expire after 10 seconds
timer.it_value.tv_usec = 10;

timer.it_interval.tv_sec = 10;                       // And every 10 seconds and 10 microseconds after that
timer.it_interval.tv_usec = 10;
setitimer(ITIMER_PROF, &timer, NULL);

while (1) {
for (volatile int i = 0; i < 100000000; i++);         // some computtaion to utilise CPU time
        sleep(1);                                    // Also make a system call (like sleep system call) to utilize system mode
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 1c.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Profiling Timer expired 1 times
// Profiling Timer expired 2 times
// ^C