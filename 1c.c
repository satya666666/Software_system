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