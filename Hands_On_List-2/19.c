/*
============================================================================
Name : 19.c
Author : Satyam Gupta
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
Date: 13th Sept. 2024
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
    const char *fifo_path = "my_fifo"; 
    // Create a FIFO special file
    if (mknod(fifo_path, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }  
    printf("FIFO %s created successfully by mknod.\n", fifo_path);
    const char *fifo_path1= "my_fifo2";
     if (mkfifo(fifo_path1, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    printf("FIFO %s created successfully by mkfifo.\n", fifo_path);
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 19.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// FIFO my_fifo created successfully by mknod.
// FIFO my_fifo created successfully by mkfifo.
