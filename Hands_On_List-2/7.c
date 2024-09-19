/*
============================================================================
Name : 7.c
Author : Satyam Gupta
Description : Write a simple program to print the created thread ids.
Date: 7th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <pthread.h>
void* thread_func(void* arg)                       // thread_func that prints the thread ID
{
printf("Thread ID: %lu\n", pthread_self());         // pthread_self() returns the unique ID of the calling thread
return NULL;
}
int main() {
pthread_t threads[3];
for (int i = 0; i < 3; i++) {
pthread_create(&threads[i], NULL, thread_func, NULL);   // pthread_create creates a new thread & each thread runs 'thread_func'
}
for (int i = 0; i < 3; i++) {
pthread_join(threads[i], NULL);                        // pthread_join waits for the thread with id 'threads[i]' to complete its execution
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 7.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Thread ID: 140544147715776
// Thread ID: 140544139323072
// Thread ID: 140544130930368