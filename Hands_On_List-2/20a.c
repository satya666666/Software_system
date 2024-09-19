/*
============================================================================
Name : 20a.c
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
#define FIFO_PATH "/tmp/myfifo"                     // FIFO file path
int main() {
    int fd;
    char *message = "Hello from sender!";
    mkfifo(FIFO_PATH, 0666);                         // Create the FIFO if it does not exist
    fd = open(FIFO_PATH, O_WRONLY);                  // Open the FIFO for writing
    if (fd == -1) {
        perror("open FIFO");
        exit(EXIT_FAILURE);
    }
    write(fd, message, strlen(message) + 1);                  // Write a message to the FIFO
    close(fd);
    printf("Message sent: %s\n", message);
    return 0;
}



// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 20a.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Message sent: Hello from sender!