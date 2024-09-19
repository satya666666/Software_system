/*
============================================================================
Name : 11.c
Author : Satyam Gupta
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date: 8th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sig_handler(int signo) {
printf("SIGINT received\n");
}
int main() {
struct sigaction sa;
// Ignore SIGINT
sa.sa_handler = SIG_IGN;
sigaction(SIGINT, &sa, NULL);
printf("SIGINT is ignored for 5 seconds\n");
sleep(5);
sa.sa_handler = sig_handler;                 // Reset SIGINT to default behavior
sigaction(SIGINT, &sa, NULL);
printf("SIGINT will now be handled\n");
while (1)                                  // Infinite loop to wait for signals
{
pause();
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 11.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// SIGINT is ignored for 5 seconds
// SIGINT will now be handled
// ^CSIGINT received
// ^CSIGINT received
// ^Z
// [3]+  Stopped                 ./a.out