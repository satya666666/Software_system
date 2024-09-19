/*
============================================================================
Name : 12.c
Author : Satyam Gupta
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date: 8th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
pid_t pid = fork();
if (pid > 0) 
{                                                                 // Parent process
sleep(2);                                                        // Ensure child becomes orphan
exit(0);
} else if (pid == 0) {
printf("I am orphan now, adopted by init process\n");           // Child process
sleep(5);                                                      // Wait to see adoption by init
printf("Child process terminating\n");
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 12.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// I am orphan now, adopted by init process
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ Child process terminating