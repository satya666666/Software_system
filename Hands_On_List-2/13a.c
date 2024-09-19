/*
============================================================================
Name : 13a.c
Author : Satyam Gupta
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 8th Sept. 2024
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sig_handler(int signo) {
printf("Caught signal %d\n", signo);
}
int main() {
signal(SIGTSTP, sig_handler);                                // This won't catch SIGSTOP
printf("your pid is %d",getpid());                            // Take the pid of the process
printf("\nWaiting for SIGSTOP...\n");
while (1) {
pause();
}
return 0;
}

// Output:
 
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 13a.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out 
// your pid is 6728
// Waiting for SIGSTOP...

// [3]+  Stopped                 ./a.out
