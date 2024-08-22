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