/*
============================================================================
Name : 30a.c
Author : Satyam Gupta
Description : Write a program to create a shared memory.
a. write some data to the shared memory
Date: 18th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
int main() {
    key_t key = ftok("/tmp", 65);                                              // Use /tmp to ensure the file always exists
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);                       // 1024 bytes of shared memory
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    char *shared_memory = (char*) shmat(shmid, NULL, 0);                    // Attach with read-write permissions
    if (shared_memory == (char*) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Writing data to shared memory...\n");                       // Write data to the shared memory
    strcpy(shared_memory, "Hello from shared memory!");
    printf("Data written to shared memory: %s\n", shared_memory);
    if (shmdt(shared_memory) == -1)                                //Detach the shared memory segment
    {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory detached successfully.\n");
    return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 30a.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Writing data to shared memory...
// Data written to shared memory: Hello from shared memory!
// Shared memory detached successfully.