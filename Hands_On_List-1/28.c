// Name - Satyam Gupta, Roll no.- MT2024134
// Question:  Write a program to get maximum and minimum real time priority

#include <sched.h>
#include <stdio.h>
int main() {
int max_priority = sched_get_priority_max(SCHED_FIFO);
int min_priority = sched_get_priority_min(SCHED_FIFO);
printf("Max Priority: %d\n", max_priority);
printf("Min Priority: %d\n", min_priority);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 28.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Max Priority: 99
// Min Priority: 1