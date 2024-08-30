// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Create a softlink for the file using 'symlink' system call

#include <unistd.h>  //for symbolic links & various system calls
#include <stdio.h>  //for input and output operations and also for perror()
int main() {
if (symlink("1shell.sh", "symlink1") == -1) // make softlink for 1shell.sh, named as symlink1 , return 0 for success & 1 for failure
{
perror("symlink");  // used for tells about the error & why this error comes
}
return 0;
}

// Output:  

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cc 1a.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ls
// 1a.c  1b.c  1c.c  1shell.sh  2.c  2shell.sh  3.c  4.c  5.c  a.out  symlink1
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cat symlink1
// # This is my first Program of Shell Scripting language i.e., used for create softlink, hardlink and Fifo by shell command.

// #!/bin/bash

// echo "Hello world, I am learning shell scripting. "