// Question: Write a program to create a file and print the file descriptor value. Use creat ( ) system call

#include <stdio.h>    // for standard input and output functions and also for perror()
#include <fcntl.h>   // for creat() and file control options
#include <unistd.h>  // for close()

int main() {
    const char *filename = "file_descriptor.txt";       // file name to be created
    int mode = S_IRUSR | S_IWUSR;                        // file mode: Read (S_IRUSR) and write (S_IRWSR) permissions for the owner
    int fd = creat(filename, mode);                      // Creating the file using creat() system call
    if (fd == -1)                                       // checking if the file creation was successful or not
    {
        perror("Error creating file");
        return 1;
    }
    printf("File '%s' created with file descriptor: %d\n", filename, fd);     // printing the file descriptor
    close(fd);                                                                // Closing the file descriptor
    return 0;
}
