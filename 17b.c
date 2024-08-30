// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd = open("tickets..txt", O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct flock lock;
    lock.l_type = F_WRLCK;            // for Write lock 
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    if (fcntl(fd, F_SETLKW, &lock) == -1)       // write lock acquired
     {
        perror("fcntl");
        close(fd);
        return 1;
    }

    char buffer[10];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead > 0) {
        int ticket_number = atoi(buffer);             // converts the data of buffer into integer
        ticket_number++;
        lseek(fd, 0, SEEK_SET);                      // repositions of Offset
        write(fd, buffer, sizeof(buffer));
        printf("New Ticket Number: %d\n", ticket_number);
    }

    lock.l_type = F_UNLCK;                 // F_UNLCK tells to release the lock previously held on the file
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 17b.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// New Ticket Number: 125