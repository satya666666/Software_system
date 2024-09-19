/*
============================================================================
Name : 30d.c
Author : Satyam Gupta
Description : Write a program to create a shared memory.
d. remove the shared memory
Date: 18th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
int main() {
    key_t key = ftok("/tmp", 65);                                           // Use /tmp to generate a key
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);                           // 1024 bytes, read/write permissions
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    char *shared_memory = (char*) shmat(shmid, NULL, 0);                      // Attach with read-write permission
    if (shared_memory == (char*) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Writing data to shared memory...\n");                            // Write some data to the shared memory
    strcpy(shared_memory, "This is data stored in shared memory.");
    printf("Data written to shared memory: %s\n", shared_memory);
    if (shmdt(shared_memory) == -1)                                    // Detach the shared memory segment from this process's address space
    {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory detached successfully.\n");
    if (shmctl(shmid, IPC_RMID, NULL) == -1)                           // Remove the shared memory segment
    {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory removed successfully.\n");
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 30d.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Writing data to shared memory...
// Data written to shared memory: This is data stored in shared memory.
// Shared memory detached successfully.
// Shared memory removed successfully.