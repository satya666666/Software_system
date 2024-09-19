/*
============================================================================
Name : 22.c
Author : Satyam Gupta
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 14th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
int main() {
int fd = open("fifo_mkfifo", O_RDONLY);
fd_set fds;
struct timeval timeout;
FD_ZERO(&fds);
FD_SET(fd, &fds);
timeout.tv_sec = 10;
timeout.tv_usec = 0;
int ret = select(fd + 1, &fds, NULL, NULL, &timeout);
if (ret > 0) {
char buffer[20];
read(fd, buffer, 20);
printf("Received: %s\n", buffer);
} else if (ret == 0) {
printf("Timeout: No data within 10 seconds\n");
} else {
printf("Select error\n");
}
close(fd);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 22.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Timeout: No data within 10 seconds

