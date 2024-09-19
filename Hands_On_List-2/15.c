/*
============================================================================
Name : 15.c
Author : Satyam Gupta
Description : Write a simple program to send some data from parent to the child process.
Date: 8th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
int main() {
int fd[2];
pipe(fd);
if (fork() == 0) {
close(fd[1]);                                // Close write end
char buffer[20];
read(fd[0], buffer, 20);
printf("Child received: %s\n", buffer);
close(fd[0]);
} else {
close(fd[0]);                                   // Close read end
write(fd[1], "Hello, child!", 13);
close(fd[1]);
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 15.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Child received: Hello, child!