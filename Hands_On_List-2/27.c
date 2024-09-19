/*
============================================================================
Name : 27.c
Author : Satyam Gupta
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
Program of message sender 
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
    key = ftok("/tmp", 65);                                         // Generate the same key as the receiver
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    msgid = msgget(key, 0666 | IPC_CREAT);                             // Create or get the message queue
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    // Prepare the message
    message.msg_type = 1;                                                 // Ensure the message type matches what the receiver expects
    strcpy(message.msg_text, "Hello from sender!");
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1)      // Send the message
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Message sent successfully!\n");
    return 0;
}




// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 27.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Message sent successfully!
