// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to display the environmental variable of the user (use environ).

#include <stdio.h>
#include <string.h>

extern char **environ;  // structure variable that holds all the environment variables as an array of strings

int main() {
    const char *var = "USER";  // The environment variable to be displayed
    char **env = environ;

    while (*env) {
        if (strncmp(*env, var, strlen(var)) == 0 && (*env)[strlen(var)] == '=')  // it actually checks the env to var "USER" found or not
        {
            printf("%s\n", *env);                               // if found the environment of var then it prints
            break;
        }
        env++;
    }

    if (!*env) {
        printf("The environment variable %s is not set.\n", var);
    }

    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 15.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// USER=satyam

