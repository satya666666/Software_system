// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to find the type of a file.
// a. Input should be taken from command line.
// b. program should be able to identify any type of a file.

#include <sys/stat.h>    // include for stat functions and macros like S_ISDIR & S_ISREG
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])   // argc tells that how many arguments count passed to the program & argv tells that argument vector like array of strings
{
if (argc != 2)                   // to ensure exactly one argument passed by the user
{
fprintf(stderr, "Usage: %s <file>\n", argv[0]);
return 1;
}
struct stat fileStat;              // a variable fileStat of type struct stat & hold the file status information once the stat() function is called
if (stat(argv[1], &fileStat) == -1)   // This line calls the stat() function to retrieve information about the file specified in argv[1] & file status information is stored in the fileStat structure
{
perror("stat");                        // if stat returns -1 , it means there is an error occured into it
return 1;
}
if (S_ISREG(fileStat.st_mode)) printf("Regular file\n");
else if (S_ISDIR(fileStat.st_mode)) printf("Directory\n");
else if (S_ISLNK(fileStat.st_mode)) printf("Symbolic link\n");
else if (S_ISCHR(fileStat.st_mode)) printf("Character device\n");
else if (S_ISBLK(fileStat.st_mode)) printf("Block device\n");
else if (S_ISFIFO(fileStat.st_mode)) printf("FIFO\n");
else if (S_ISSOCK(fileStat.st_mode)) printf("Socket\n");
else printf("Unknown file type\n");
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 14.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out 14.c
// Regular file