/*
============================================================================
Name : 26.c
Author : Satyam Gupta
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 15th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct msg_buffer {
long msg_type;
char msg_text[100];
} message;
int main() {
key_t key = ftok("progfile", 65);
int msgid = msgget(key, 0666 | IPC_CREAT);
message.msg_type = 1;
strcpy(message.msg_text, "Hello from Message Queue");
msgsnd(msgid, &message, sizeof(message), 0);
printf("Data sent: %s\n", message.msg_text);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 26.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Data sent: Hello from Message Queue