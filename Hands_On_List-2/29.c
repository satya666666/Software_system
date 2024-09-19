/*
============================================================================
Name : 29.c
Author : Satyam Gupta
Description : Write a program to remove the message queue.
Date: 18th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main() {
key_t key = ftok("progfile", 65);
int msgid = msgget(key, 0666 | IPC_CREAT);
msgctl(msgid, IPC_RMID, NULL);
printf("Message Queue removed\n");
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 29.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Message Queue removed

