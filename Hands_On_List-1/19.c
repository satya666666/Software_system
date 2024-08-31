// Name - Satyam Gupta, Roll no.- MT2024134
// Question:  Write a program to find out time taken to execute getpid system call. Use time stamp counter.

#include <stdio.h>
#include <time.h>      // For clock_gettime and struct timespec
#include <unistd.h>    // / For getpid
int main() {
struct timespec start, end;      
clock_gettime(CLOCK_MONOTONIC, &start);            // Get the current time before the operation
getpid();                                         // Call a simple function to get the process ID 
clock_gettime(CLOCK_MONOTONIC, &end);             // Get the current time after the operation

// Calculate the time difference in seconds and nanoseconds
long seconds = end.tv_sec - start.tv_sec;           
long nanoseconds = end.tv_nsec - start.tv_nsec;

double elapsed = seconds + nanoseconds*1e-9;
printf("Time taken: %.9f seconds\n", elapsed);           // elapsed time
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 19.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Time taken: 0.000003907 seconds