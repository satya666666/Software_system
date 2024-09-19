/*
============================================================================
Name : 27a.c
Author : Satyam Gupta
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
Date: 15th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct msg_buffer                                                         // Define a structure for the message
{
    long msg_type;
    char msg_text[100];
};
int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;
                                                                        // Generate a unique key using an existing file and a project identifier
    key = ftok("/tmp", 65);                                                // Using /tmp as it should always exist
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    msgid = msgget(key, 0666 | IPC_CREAT);                               // Create a message queue and return identifier
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    printf("Waiting to receive message...\n");
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) // Receive the message with flag 0 (blocking mode)  We are waiting for a message with msg_type = 1
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    // Display the received message
    printf("Received Message: %s\n", message.msg_text);
    if (msgctl(msgid, IPC_RMID, NULL) == -1)                        // Destroy the message queue after receiving the message
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}




// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc -o 27a  27a.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./27a
// Waiting to receive message...
// Received Message: Hello from sender!

