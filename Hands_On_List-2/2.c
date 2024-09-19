/*
============================================================================
Name : 2.c
Author : Satyam Gupta
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 6th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>

int main() {
    
    struct rlimit rl;                 // Define a struct to hold the resource limits
    getrlimit(RLIMIT_NOFILE, &rl);   // Get the resource limits for the maximum number of open file descriptors by the help of (RLIMIT_NOFILE)
    printf("Max file descriptors: %ld (soft limit), %ld (hard limit)\n", rl.rlim_cur, rl.rlim_max);         // Print the soft limit and hard limit for open file descriptors
    getrlimit(RLIMIT_STACK, &rl);    // // Get the resource limits for the maximum stack size
    printf("Max stack size: %ld bytes (soft limit), %ld bytes (hard limit)\n", rl.rlim_cur, rl.rlim_max);  // soft limit is current link & hard limit is the maximum link

    return 0;  
}




// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 2.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Max file descriptors: 1048576 (soft limit), 1048576 (hard limit)
// Max stack size: 8388608 bytes (soft limit), -1 bytes (hard limit)   

// -1 means RLIM_INFINITY