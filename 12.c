// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to find out the opening mode of a file. Use fcntl.

#include <fcntl.h>                    // For open, fcntl and file status flags like O_RDWR, O_CREAT and etc. 
#include <stdio.h>
#include <unistd.h>                   // For close
int main() {
int fd = open("Example.txt", O_RDWR | O_CREAT, 0644);
if (fd == -1) {
perror("open");
return 1;
}
int flags = fcntl(fd, F_GETFL);          // fcntl tooks the flag status of file descriptor & flag stores the file status returned by fcntl
if (flags == -1) {
perror("fcntl");
close(fd);
return 1;
}
printf("File opening mode: ");
if (flags & O_RDONLY) printf("O_RDONLY ");
if (flags & O_WRONLY) printf("O_WRONLY ");
if (flags & O_RDWR) printf("O_RDWR ");
if (flags & O_CREAT) printf("O_CREAT ");
if (flags & O_APPEND) printf("O_APPEND ");
if (flags & O_TRUNC) printf("O_TRUNC ");
printf("\n");
close(fd);
return 0;
}

// Output: 

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 12.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// File opening mode: O_RDWR 