// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
// a. use dup
// b. use dup2
// c. use fcntl

#include <fcntl.h>            // for open() and fcntl() 
#include <unistd.h>           // for dup(), dup2(), write(), & close() operations
#include <stdio.h>             
#include <string.h>          // for strlen function

int main() {
    int fd = open("file.txt", O_RDWR | O_CREAT | O_APPEND, 0644);       // Open the file in append mode
    if (fd == -1) {
        perror("open");
        return 1;
    }
    int fd_dup = dup(fd);                                             // Duplicate the file descriptor using dup
    if (fd_dup == -1) {
        perror("dup");
        close(fd);
        return 1;
    }
    int fd_dup2 = dup2(fd, fd_dup + 1);                            // Duplicate the file descriptor using dup2, to a new descriptor
    if (fd_dup2 == -1) {
        perror("dup2");
        close(fd);
        close(fd_dup);
        return 1;
    }
    int fd_fcntl = fcntl(fd, F_DUPFD, fd_dup2 + 1);                // Duplicate the file descriptor using fcntl, to a new descriptor
    if (fd_fcntl == -1) {
        perror("fcntl");
        close(fd);
        close(fd_dup);
        close(fd_dup2);
        return 1;
    }
    // Write to the file using the original and duplicated file descriptors
    const char *data = "fd: Writing to file.\n";
    const char *data1 = "fd_dup: Writing to file.\n";
    const char *data2 = "fd_dup2: Writing to file.\n";
    const char *data3 = "fd_fcntl: Writing to file.\n";
    if (write(fd, data, strlen(data)) == -1) {
        perror("Error in fd");
    }
    if (write(fd_dup, data1, strlen(data1)) == -1) {
        perror("Error in fd_dup");
    }
    if (write(fd_dup2, data2, strlen(data2)) == -1) {
        perror("Error in fd_dup2");
    }
    if (write(fd_fcntl, data3, strlen(data3)) == -1) {
        perror("Error in fd_fcntl");
    }

    // Close all file descriptors
    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);

    return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 11.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cat file.txt
// fd: Writing to file.
// fd_dup: Writing to file.
// fd_dup2: Writing to file.
// fd_fcntl: Writing to file.