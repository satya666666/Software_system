/*
============================================================================
Name : 28.c
Author : Satyam Gupta
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure).
Date: 17th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main() {
key_t key = ftok("progfile", 65);
int msgid = msgget(key, 0666 | IPC_CREAT);
struct msqid_ds buf;
msgctl(msgid, IPC_STAT, &buf);
buf.msg_perm.mode = 0644;
msgctl(msgid, IPC_SET, &buf);
printf("Message Queue permissions updated to 0644\n");
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 28.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Message Queue permissions updated to 0644