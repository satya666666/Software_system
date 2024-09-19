/*
============================================================================
Name : 21b.c
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
#define FIFO1 "/tmp/myfifo1"                                // FIFO for receiving messages
#define FIFO2 "/tmp/myfifo2"                                // FIFO for sending messages
int main() {
    int fd1, fd2;
    char buffer[100];
    char *reply = "Hello from receiver!";
    mkfifo(FIFO1, 0666);                                           // Create the FIFOs if they don't exist
    mkfifo(FIFO2, 0666);
    fd1 = open(FIFO1, O_RDONLY);                                   // Open FIFO1 for reading (sender -> receiver)                                      
    if (fd1 == -1) {
        perror("open FIFO1");
        exit(EXIT_FAILURE);
    }
    read(fd1, buffer, sizeof(buffer));                                            // Read the message from FIFO1
    close(fd1);
    printf("Message received from sender: %s\n", buffer);
    fd2 = open(FIFO2, O_WRONLY);                                               // Open FIFO2 for writing (receiver -> sender)
    if (fd2 == -1) {
        perror("open FIFO2");
        exit(EXIT_FAILURE);
    }
    write(fd2, reply, strlen(reply) + 1);                                   // Write a reply to FIFO2
    close(fd2);
    printf("Reply sent to sender: %s\n", reply);
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 21b.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Message received from sender: Hello from sender!
// Reply sent to sender: Hello from receiver!