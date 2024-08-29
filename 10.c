// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
// a. check the return value of lseek
// b. open the file with od and check the empty spaces in between the data.

#include <fcntl.h>      // for open() and fcntl() control opeartions 
#include <unistd.h>     // for close(), lseek(), write()
#include <stdio.h>
int main() {
int fd = open("file.txt", O_RDWR | O_CREAT, 0644);     // 0644 means that read and write permission for owner, but groups & others do read also. 
if (fd == -1) {
perror("open");
return 1;
}
const char *data1 = "1234567890";
const char *data2 = "abcdefghij";
write(fd, data1, 10);
off_t offset = lseek(fd, 10, SEEK_SET);       // It moves the file pointer 10 bytes forward 
if (offset == -1) {
perror("lseek");
close(fd);
return 1;
}
write(fd, data2, 10);                        // write 10 bytes of data from which the file pointer points
close(fd);
return 0;
}

// Output: 

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 10.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cat file.txt
// 1234567890abcdefghij
