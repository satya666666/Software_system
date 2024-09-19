/*
============================================================================
Name : 30b.c
Author : Satyam Gupta
Description : Write a program to create a shared memory.
b. attach with O_RDONLY and check whether you are able to overwrite.
Date: 18th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
int main() {
    key_t key = ftok("/tmp", 65);                                        // Using /tmp to generate key
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);                       // 1024 bytes of shared memory
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    char *shared_memory = (char*) shmat(shmid, NULL, SHM_RDONLY);          // Attach with read-only permission
    if (shared_memory == (char*) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Data read from shared memory: %s\n", shared_memory);
    printf("Attempting to write to shared memory in read-only mode...\n");
    strcpy(shared_memory, "Trying to overwrite!");
    if (shmdt(shared_memory) == -1)                                // Detach the shared memory
    {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    return 0;
}



// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 30b.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Data read from shared memory: Hello from shared memory!
// Attempting to write to shared memory in read-only mode...
// Segmentation fault (core dumped)