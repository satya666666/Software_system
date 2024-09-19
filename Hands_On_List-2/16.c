/*
============================================================================
Name : 16.c
Author : Satyam Gupta
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication. 
Date: 11th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
int main() {
int fd1[2], fd2[2];
pipe(fd1);
pipe(fd2);
if (fork() == 0) {
close(fd1[1]);
close(fd2[0]);
char buffer[20];
read(fd1[0], buffer, 20);
printf("Child received: %s\n", buffer);
write(fd2[1], "Hello, parent!", 14);
close(fd1[0]);
close(fd2[1]);
} else {
close(fd1[0]);
close(fd2[1]);
write(fd1[1], "Hello, child!", 13);
char buffer[20];
read(fd2[0], buffer, 20);
printf("Parent received: %s\n", buffer);
close(fd1[1]);
close(fd2[0]);
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 16.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Child received: Hello, child!
// Parent received: Hello, parent!