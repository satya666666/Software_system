/*
============================================================================
Name : 24.c
Author : Satyam Gupta
Description : Write a program to create a message queue and print the key and message queue id.
Date: 14th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main() {
key_t key = ftok("progfile", 65);
int msgid = msgget(key, 0666 | IPC_CREAT);
printf("Message Queue Key: %d, ID: %d\n", key, msgid);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 24.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Message Queue Key: -1, ID: 0