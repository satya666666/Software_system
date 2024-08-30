// Name - Satyam Gupta, Roll no.- MT2024134
// Question - Create the fifo() pipe by mkfifo().

#include <sys/types.h>   // header file for data types
#include <sys/stat.h>    //for handling makfifo() functions
#include <stdio.h>       //for input and output operations and also for perror()
int main() 
{
if (mkfifo("fifo1", 0666) == -1)     //this has to be create the fifo() pipe, 0666 for read and write permission
 {
perror("mkfifo");                        //used for tells about the error & why this error comes
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cc 1c.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ls
// 1a.c  1b.c  1c.c  1shell.sh  2.c  2shell.sh  3.c  4.c  5.c  a.out  fifo1  symlink1  symlink2



