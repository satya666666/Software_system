// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to execute an executable program.
// a. use some executable program
// b. pass some input to an executable program. (for example execute an executable of $./a.out name)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Path to the executable file
    const char *execut = "./28.out";
    // Argument to be passed to the executable
    const char *arg = "delhi";
    
    // Construct the command to run the executable with the argument
    char command[512];
    snprintf(command, sizeof(command), "%s %s", execut, arg);
    
    // Run the command
    int status = system(command);
    
    // Check if system call failed
    if (status == -1) {
        perror("Problem running the file");
        return 1; // Return 1 to indicate error
    }
    
    // Check the exit status of the command
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        printf("Executable exited with status %d\n", WEXITSTATUS(status));
        return 1; // Return 1 to indicate error
    }
    
    // Return 0 to indicate success
    return 0;
}


// Output: 

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cc 26.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Max Priority: 99
// Min Priority: 1