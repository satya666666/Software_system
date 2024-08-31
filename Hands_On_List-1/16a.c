// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to perform mandatory locking. a. Implement write lock

#include <fcntl.h>           // for open and fcntl
#include <unistd.h>          // for close() & SEEK_SET
#include <stdio.h>
int main() {
int fd = open("example.txt", O_RDWR | O_CREAT, 0644);            // open the example.txt file & 0644 means permission of file like owner can read & write both but others can do read only
if (fd == -1)                // if open returns -1 to fd then it prints error and close
{
perror("open");
return 1;
}
struct flock lock;             // Declares a file lock of structure type 
lock.l_type = F_WRLCK;        // write lock acquired
lock.l_whence = SEEK_SET;     // SEEK_SET means starting point is the beginning of file
lock.l_start = 0;             // lock start at beginning
lock.l_len = 0;               // length of the lock & 0 means the lock extends to end 
if (fcntl(fd, F_SETLKW, &lock) == -1)    // F_SETLKW is used to acquire a lock on the example .txt file
{
perror("fcntl");
}
printf("Write lock acquired.\n");
close(fd);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ g++ 16a.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Write lock acquired.

