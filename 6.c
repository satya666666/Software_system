// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls.

#include <unistd.h>  // for system calls like read & write
int main() 
{
char buffer[256];    // buffer can store maximum 255 characters for read
size_t bytesRead;   // to store the size of block of data in bytes

bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);     // standard input file desciptor & read return the number of bytes successfully read else return -1 & ie., stored in bytesRead

if(bytesRead  > 0)  
{
write(STDOUT_FILENO, buffer, bytesRead);  // standard outputfile descriptor for data to be written, bytesRead tell how much bytes of data to be written. 
}

return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 6.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// I have prepared Software System file.
// I have prepared Software System file.