/*
============================================================================
Name : 4.c
Author : Satyam Gupta
Description : Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.
Date: 6th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
unsigned long long rdtsc()                     // Function to read the Time Stamp Counter (TSC) from the CPU
{                                              // TSC is a 64-bit register present in modern CPUs that counts the number of cycles until reset
unsigned long long d;                          // Variable to store the TSC value
__asm__ __volatile__("rdtsc" : "=A" (d));      // assembly instructions to read the TSC (rdtsc instruction)
return d;
}
int main() {
unsigned long long start, end;
int i;
start = rdtsc();                            // record the TSC value before go for LOOP
for (i = 0; i < 100; i++) {
getppid();
}
end = rdtsc();                              // record the TSC value after completing the LOOP
printf("Time taken to execute 100 getppid() calls: %llu cycles\n", (end - start));                    // print the total number of CPU cycles taken
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 4.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Time taken to execute 100 getppid() calls: 199764 cycles
