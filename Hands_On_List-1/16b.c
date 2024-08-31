// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to perform mandatory locking. b. Implement read lock

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main() {
int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
if (fd == -1) {
perror("open");
return 1;
}
struct flock lock;                  // Declares a file lock of structure type 
lock.l_type = F_RDLCK;              // Read lock acquired
lock.l_whence = SEEK_SET;           
lock.l_start = 0;
lock.l_len = 0;
if (fcntl(fd, F_SETLKW, &lock) == -1)        // F_SETLKW is used to acquire a lock on the example .txt file
{
perror("fcntl");
}
printf("Read lock acquired.\n");
close(fd);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ g++ 16b.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Read lock acquired.
