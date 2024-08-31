// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to create an orphan process

#include <unistd.h>
#include <stdio.h>
int main() {
pid_t pid = fork();
if (pid == -1) {
perror("fork");
return 1;
} else if (pid == 0) {
// Child process
printf("Child PID: %d\n", getpid());
sleep(1); // Allow time for parent to exit
printf("Child PID: %d\n", getpid());
} else {
// Parent process
_exit(0);
}
return 0;
}

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 24.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Child PID: 11647
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ Child PID: 11647
