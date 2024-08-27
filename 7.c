// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to copy file1 into file2 ($cp file1 file2).

#include <fcntl.h>   // for open the file
#include <unistd.h>  // for read , write and close system calls
#include <stdio.h>   
int main() {
int src_fd = open("Example.txt", O_RDONLY);  // Example.txt file is opened in read only mode
if (src_fd == -1) {
perror("open Source file");
return 1;
}
int dest_fd = open("file2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);    // this file is opend in write mode only or not exist then created or all data should be deleted before created
if (dest_fd == -1)                                                      // 0644 means that it can be read or write by owner but others only read it. 
{
perror("open Destination file");
close(src_fd);
return 1;
}
char buffer[4096];
size_t bytesRead;
while ((bytesRead = read(src_fd, buffer, sizeof(buffer))) > 0) {
write(dest_fd, buffer, bytesRead);
}
close(src_fd);     // close the source file descriptor 
close(dest_fd);    // close the destination file descriptor
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 7.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cat Example.txt
// I am the student of IIITB M.tech
// Now I am doing the hands on of Software System
// I learn about System call, Shell scripting and  Process Management.satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cat file2.txt
// I am the student of IIITB M.tech
// Now I am doing the hands on of Software System
// I learn about System call, Shell scripting and  Process Management.