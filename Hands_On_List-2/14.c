/*
============================================================================
Name : 14.c
Author : Satyam Gupta
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 8th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
int main() {
int fd[2];
pipe(fd);
if (fork() == 0) {
close(fd[0]);                             // Close read end
write(fd[1], "Hello, parent!", 14);
close(fd[1]);
} else {
char buffer[20];
close(fd[1]);                             // Close write end
read(fd[0], buffer, 20);
printf("Received from child: %s\n", buffer);
close(fd[0]);
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 14.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Received from child: Hello, parent!