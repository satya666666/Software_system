// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
int main() {
for (int i = 0; i < 3; i++) {
pid_t pid = fork();
if (pid == -1) {
perror("fork");
return 1;
} else if (pid == 0) {
printf("Child PID: %d\n", getpid());
_exit(0);
}
}
int status;
pid_t pid = waitpid(-1, &status, 0);
if (pid == -1) {
perror("waitpid");
} else {
printf("Waited for child PID: %d\n", pid);
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 25.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Child PID: 11797
// Child PID: 11795
// Waited for child PID: 11797
// Child PID: 11796