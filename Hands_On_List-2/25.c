/*
============================================================================
Name : 25.c
Author : Satyam Gupta
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 15th Sept. 2024
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
printf("Access permission: %o\n", buf.msg_perm.mode);
printf("UID: %d, GID: %d\n", buf.msg_perm.uid, buf.msg_perm.gid);
printf("Last message sent: %ld\n", buf.msg_stime);
printf("Last message received: %ld\n", buf.msg_rtime);
printf("Last change in queue: %ld\n", buf.msg_ctime);
printf("Current number of messages: %lu\n", buf.msg_qnum);
printf("Max bytes allowed: %lu\n", buf.msg_qbytes);
printf("PID of last msgsnd: %d, msgrcv: %d\n", buf.msg_lspid, buf.msg_lrpid);
return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 25.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Access permission: 666
// UID: 1000, GID: 1000
// Last message sent: 0
// Last message received: 0
// Last change in queue: 1726156848
// Current number of messages: 0
// Max bytes allowed: 16384
// PID of last msgsnd: 0, msgrcv: 0

