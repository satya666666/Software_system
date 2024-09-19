/*
============================================================================
Name : 32.c
Author : Satyam Gupta
Description : Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
Date: 18th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
void P(int semid) {
struct sembuf p = {0, -1, SEM_UNDO};
semop(semid, &p, 1);
}
void V(int semid) {
struct sembuf v = {0, 1, SEM_UNDO};
semop(semid, &v, 1);
}
int main() {
key_t key = ftok("semfile", 65);
int semid = semget(key, 1, 0666 | IPC_CREAT);
semctl(semid, 0, SETVAL, 1);
if (fork() == 0) {
P(semid);
printf("Child: Entering critical section\n");
sleep(2);
printf("Child: Leaving critical section\n");
V(semid);
} else {
P(semid);
printf("Parent: Entering critical section\n");
sleep(2);
printf("Parent: Leaving critical section\n");
V(semid);
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 32.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Parent: Entering critical section
// Parent: Leaving critical section
// Child: Entering critical section
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ Child: Leaving critical section