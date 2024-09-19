/*
============================================================================
Name : 6.c
Author : Satyam Gupta
Description : Write a simple program to create three threads.
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <pthread.h>
void* thread_func(void* arg)   // thread function that print the thread number
{
printf("Thread %ld is running\n", (long)arg);                // arg is the thread index that passed during thread creation
return NULL;
}
int main() {
pthread_t threads[3];                              // array to hold the 3 thread identifiers
for (long i = 0; i < 3; i++) {
pthread_create(&threads[i], NULL, thread_func, (void*)i);       // pthread_create creates a new thread & thread runs the thread_func & passed as the i argument
}
for (int i = 0; i < 3; i++) {
pthread_join(threads[i], NULL);                                 // pthread_join waits for the thread with id 'threads[i]' to complete execution
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 6.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Thread 0 is running
// Thread 2 is running
// Thread 1 is running