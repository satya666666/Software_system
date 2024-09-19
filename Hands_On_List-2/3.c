/*
============================================================================
Name : 3.c
Author : Satyam Gupta
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 6th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
int main() {
struct rlimit rl;

rl.rlim_cur = 1024;               // Set new limit for the maximum file descriptors
rl.rlim_max = 2048;
setrlimit(RLIMIT_NOFILE, &rl);                

getrlimit(RLIMIT_NOFILE, &rl);            // Verify the new limits
printf("New max file descriptors: %ld (soft limit), %ld (hard limit)\n", rl.rlim_cur, rl.rlim_max);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 3.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// New max file descriptors: 1024 (soft limit), 2048 (hard limit)