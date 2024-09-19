/*
============================================================================
Name : 9.c
Author : Satyam Gupta
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sig_handler(int signo) {
printf("SIGINT received\n");
}
int main() {
signal(SIGINT, SIG_IGN);                             // Ignore SIGINT
printf("SIGINT is ignored for 5 seconds\n");
sleep(5);
signal(SIGINT, sig_handler);                          // Reset SIGINT to default behavior
printf("SIGINT will now be handled\n");
while (1)                                             // Infinite loop to wait for signals
{
pause();
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 9.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// SIGINT is ignored for 5 seconds
// SIGINT will now be handled
// ^CSIGINT received
// ^Z
// [2]+  Stopped                 ./a.out