// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a simple program to execute in an infinite loop at the background.

#include<unistd.h>  // use this header for sleep() 
#include<stdio.h>   // for standard input and output
int main ()
{
    for(;;)  // loop that runs indefinitely
    {
        sleep(2);      //sleep or pause the execution for 2 seconds
    }
    return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cc 2.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// ^C