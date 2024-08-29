// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Create a hardlink for the file using 'link' system call.

#include <unistd.h>    //for  links & various system calls
#include <stdio.h>     //for input and output operations and also for perror()
int main() {
if (link("2shell.sh", "symlink2") == -1)     // make hardlink for 1shell.sh, named as symlink2 , return 0 for success & 1 for failure
{                       
perror("link");                               // used for tells about the error & why this error comes
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cc 1b.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ls
// 1a.c  1b.c  1c.c  1shell.sh  2.c  2shell.sh  3.c  4.c  5.c  a.out  symlink1  symlink2
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cat symlink2
// # This is my first Program of Shell Scripting language i.e., used for create softlink, hardlink and Fifo by shell command.

// #!/bin/bash

// echo "This is the basic program for hardlink to make by system call. 
