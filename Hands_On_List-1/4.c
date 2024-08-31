// Name - Satyam Gupta, Roll no.- MT2024134
//Question: Write a program to open an existing file with read write mode. Try O_EXCL (exclusive flags) flag also.

#include <fcntl.h>    //use for exlusive flags(O_EXCL) & open
#include <stdio.h>    //for input and ouput
#include <unistd.h>   //for closing the file descriptor like close(fd)
int main() {
int fd = open("file_descriptor.txt", O_RDWR | O_EXCL);   //O_RDWR-- ths allows file to be both read and write mode, O_EXCL--- use for create or open file.
if (fd == -1)
{
perror("open");
} else {
printf("File descriptor: %d\n", fd);
close(fd);
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cc 4.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// File descriptor: 3
