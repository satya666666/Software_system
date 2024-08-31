// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to run a script at a specific time using a Daemon process.

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
pid_t pid = fork();
if (pid < 0) {
perror("fork");
return 1;
}
if (pid > 0) {
_exit(0);
}
if (setsid() < 0) {
perror("setsid");
return 1;
}
umask(0);
chdir("/");
int fd = open("/dev/null", O_RDWR);
dup2(fd, STDIN_FILENO);
dup2(fd, STDOUT_FILENO);
dup2(fd, STDERR_FILENO);
close(fd);
// Your script to run at a specific time goes here
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 30.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out

// The program itself has no output.

