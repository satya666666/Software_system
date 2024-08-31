// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program, call fork and print the parent and child process id.

#include<unistd.h>
#include <stdio.h>
int main() {
pid_t pid = fork();               // Create new process by forking the current process
if (pid == -1) {
perror("fork");
return 1;
} else if (pid == 0)               // if child process
{
printf("Child PID: %d\n", getpid());
} else {
printf("Parent PID: %d\n", getpid());
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 21.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Parent PID: 11011
// Child PID: 11012