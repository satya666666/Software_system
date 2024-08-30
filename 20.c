// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Find out the priority of your running program. Modify the priority with nice command.

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main() {
    pid_t pid = getpid();

    printf("Current Priority: %d\n", getpriority(PRIO_PROCESS, pid));

    nice(5); // Increase niceness by 5 (lower the priority)

    printf("New Priority: %d\n", getpriority(PRIO_PROCESS, pid));

    while (0) sleep(1); // Keep the program running

    return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 20.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Current Priority: 0
// New Priority: 5