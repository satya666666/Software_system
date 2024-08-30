// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.

#include <fcntl.h>       // for open the file
#include <unistd.h>      // for read, write and close operations
#include <stdio.h>
int main() {
int fd = open("Example.txt", O_RDONLY);   // open the Exmaple.txt in read mode only
if (fd == -1) {
perror("open");
return 1;
}
char buffer[256];
size_t bytesRead;                          // to store the size of block of data in bytes
while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
buffer[bytesRead] = '\0';                 // add null character to the end of the string
printf("%s", buffer);
}
close(fd);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 8.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// I am the student of IIITB M.tech
// Now I am doing the hands on of Software System
// I learn about System call, Shell scripting and  Process Management.