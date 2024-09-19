/*
============================================================================
Name : 13b.c
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
int main() {
pid_t pid;
printf("Enter the PID to send SIGSTOP: ");
scanf("%d", &pid);
kill(pid, SIGSTOP);
printf("Sent SIGSTOP to %d\n", pid);
return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 13b.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Enter the PID to send SIGSTOP: 6728
// Sent SIGSTOP to 6728