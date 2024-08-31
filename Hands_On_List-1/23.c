// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to create a Zombie state of the running program.

#include <unistd.h>
#include <stdio.h>
int main() {
pid_t pid = fork();
if (pid == -1) {
perror("fork");
return 1;
} else if (pid == 0) {
// Child process
_exit(0);
} else {
// Parent process
sleep(60); // Allow time for parent to exit
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 23.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// ^C

// The program itself has no output.
// The child process exits immediately, possibly becoming a zombie.
// The parent process sleeps for 60 seconds and then exits.