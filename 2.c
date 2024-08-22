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