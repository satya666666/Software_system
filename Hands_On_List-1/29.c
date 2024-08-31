// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR).

#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = getpid();
    int policy = sched_getscheduler(pid);

    if (policy == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    }

    printf("Current policy: %s\n", 
           (policy == SCHED_FIFO) ? "SCHED_FIFO" :
           (policy == SCHED_RR) ? "SCHED_RR" : "SCHED_OTHER");

    struct sched_param param = {.sched_priority = 1};

    if (sched_setscheduler(pid, SCHED_RR, &param) == -1) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }

    printf("New policy: SCHED_RR\n");
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 29.c -o 29
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ sudo ./29
// Current policy: SCHED_OTHER
// New policy: SCHED_RR

