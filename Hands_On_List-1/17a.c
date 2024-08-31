// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to simulate online ticket reservation. Implement write lock & Write a program to open a file, store a ticket number and exit.

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>          // used for strlen

int main() {
    int fd = open("tickets..txt", O_RDWR | O_CREAT | O_TRUNC, 0644);   // 0644 means owner can both read & write both & others can read
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char ticket_number[10];
    snprintf(ticket_number, sizeof(ticket_number), "%d", 124);    // Converts the integer 124 to a string and stores it in the ticket_number array

    // Use strlen to write only the used bytes (excluding the null terminator)
    ssize_t bytes_written = write(fd, ticket_number, strlen(ticket_number));    // Writes the contents of ticket_number to the file represented by the file descriptor fd
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 17a.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cat tickets..txt
// 124