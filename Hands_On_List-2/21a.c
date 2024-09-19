/*
============================================================================
Name : 21a.c
Author : Satyam Gupta
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 13th Sept. 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#define FIFO1 "/tmp/myfifo1"                              // FIFO for sending messages
#define FIFO2 "/tmp/myfifo2"                              // FIFO for receiving messages
int main() {
    int fd1, fd2;
    char *message = "Hello from sender!";
    char buffer[100];
    mkfifo(FIFO1, 0666);                                    // Create the FIFOs if they don't exist
    mkfifo(FIFO2, 0666);
    fd1 = open(FIFO1, O_WRONLY);                              // Open FIFO1 for writing (sender -> receiver)
    if (fd1 == -1) {
        perror("open FIFO1");
        exit(EXIT_FAILURE);
    }
    write(fd1, message, strlen(message) + 1);                       // Write a message to FIFO1
    close(fd1);
    printf("Message sent to receiver: %s\n", message);
    fd2 = open(FIFO2, O_RDONLY);                                   // Open FIFO2 for reading (receiver -> sender)
    if (fd2 == -1) {
        perror("open FIFO2");
        exit(EXIT_FAILURE);
    }
    read(fd2, buffer, sizeof(buffer));                            // Read the reply from FIFO2
    close(fd2);
    printf("Message received from receiver: %s\n", buffer);
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 21a.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Message sent to receiver: Hello from sender!
// Message received from receiver: Hello from receiver!