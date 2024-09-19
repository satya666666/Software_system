/*
============================================================================
Name : 27b.c
Author : Satyam Gupta
Description : Write a program to receive messages from the message queue.
b. with IPC_NOWAIT as a flag
Date: 15th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
struct msg_buffer                                                             // Define a structure for the message
{
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;
    // Use an existing file (like /tmp) for generating the key
    key = ftok("/tmp", 65);                                                         // Using /tmp as it should always exist
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    msgid = msgget(key, 0666 | IPC_CREAT);                                          // Create a message queue and return identifier
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    printf("Trying to receive message...\n");
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, IPC_NOWAIT) == -1)             // Attempt to receive the message with IPC_NOWAIT flag (non-blocking mode)
    {
        if (errno == ENOMSG) {
            printf("No message available in the queue (non-blocking).\n");
        } else {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Received Message: %s\n", message.msg_text);                            // Display the received message if it was successfully received
    }
    if (msgctl(msgid, IPC_RMID, NULL) == -1)                                          // Destroy the message queue after receiving the message
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 27b.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Trying to receive message...
// Received Message: Hello from sender!