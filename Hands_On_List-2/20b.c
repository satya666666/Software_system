/*
============================================================================
Name : 20b.c
Author : Satyam Gupta
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 13th Sept. 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_PATH "/tmp/myfifo"                        // FIFO file path
int main() {
    int fd;
    char buffer[100];
    fd = open(FIFO_PATH, O_RDONLY);                       // Open the FIFO for reading
    if (fd == -1) {
        perror("open FIFO");
        exit(EXIT_FAILURE);
    }
    read(fd, buffer, sizeof(buffer));                      // Read the message from the FIFO
    close(fd);
    printf("Message received: %s\n", buffer);
    unlink(FIFO_PATH);                                      // Remove the FIFO after usage
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 20b.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Message received: Hello from sender!