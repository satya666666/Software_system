/*
============================================================================
Name : 18.c
Author : Satyam Gupta
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 13th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
int fd[2];
pipe(fd);
if (fork() == 0) {
close(fd[0]);
dup2(fd[1], STDOUT_FILENO);
close(fd[1]);
execlp("ls", "ls", "-l", NULL);
} else {
close(fd[1]);
int fd2[2];
pipe(fd2);
if (fork() == 0) {
close(fd2[0]);
dup2(fd[0], STDIN_FILENO);
close(fd[0]);
dup2(fd2[1], STDOUT_FILENO);
close(fd2[1]);
execlp("grep", "grep", "^d", NULL);
} else {
close(fd[0]);
close(fd2[1]);
dup2(fd2[0], STDIN_FILENO);
close(fd2[0]);
execlp("wc", "wc", NULL);
}
}
return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 18.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
//       0       0       0