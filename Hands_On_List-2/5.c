/*
============================================================================
Name : 5.c
Author : Satyam Gupta
Description : Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory.
Date: 6th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
int main() {
printf("Max length of arguments to exec family: %ld bytes\n", sysconf(_SC_ARG_MAX));
printf("Max number of simultaneous processes per user: %ld\n", sysconf(_SC_CHILD_MAX));
printf("Number of clock ticks per second: %ld\n", sysconf(_SC_CLK_TCK));
printf("Max number of open files: %ld\n", sysconf(_SC_OPEN_MAX));
printf("Size of a page: %ld bytes\n", sysconf(_SC_PAGESIZE));
printf("Total number of pages: %ld\n", sysconf(_SC_PHYS_PAGES));
printf("Number of currently available pages: %ld\n", sysconf(_SC_AVPHYS_PAGES));
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 5.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Max length of arguments to exec family: 2097152 bytes
// Max number of simultaneous processes per user: 30971
// Number of clock ticks per second: 100
// Max number of open files: 1048576
// Size of a page: 4096 bytes
// Total number of pages: 2000911
// Number of currently available pages: 410346
