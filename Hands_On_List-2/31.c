/*
============================================================================
Name : 31.c
Author : Satyam Gupta
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date: 18th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main() {
key_t key = ftok("semfile", 65);
// Binary Semaphore
int semid_bin = semget(key, 1, 0666 | IPC_CREAT);
semctl(semid_bin, 0, SETVAL, 1);
printf("Binary Semaphore created with ID: %d\n", semid_bin);
// Counting Semaphore
int semid_count = semget(key, 1, 0666 | IPC_CREAT);
semctl(semid_count, 0, SETVAL, 5);
printf("Counting Semaphore created with ID: %d\n", semid_count);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 31.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Binary Semaphore created with ID: 0
// Counting Semaphore created with ID: 0
