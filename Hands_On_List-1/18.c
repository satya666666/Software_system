// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to perform Record locking.
// a. Implement write lock
// b. Implement read lock
// Create three records in a file. Whenever you access a particular record, first lock it then modify/access
// to avoid race condition.

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define FILENAME "records.txt"
#define RECORD_SIZE 50

void write_record(int fd, int record_num, const char *data) {
    struct flock lock;
    lock.l_type = F_WRLCK;  // Write lock
    lock.l_whence = SEEK_SET;
    lock.l_start = record_num * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;

    // Acquire write lock
    fcntl(fd, F_SETLKW, &lock);

    // Write data to the specific record
    lseek(fd, record_num * RECORD_SIZE, SEEK_SET);
    write(fd, data, strlen(data));

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
}

void read_record(int fd, int record_num, char *buffer) {
    struct flock lock;
    lock.l_type = F_RDLCK;  // Read lock
    lock.l_whence = SEEK_SET;
    lock.l_start = record_num * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;

    // Acquire read lock
    fcntl(fd, F_SETLKW, &lock);

    // Read data from the specific record
    lseek(fd, record_num * RECORD_SIZE, SEEK_SET);
    read(fd, buffer, RECORD_SIZE);

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
}

int main() {
    int fd = open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Initialize three records
    write_record(fd, 0, "Record 1: Initial Data1\n");
    write_record(fd, 1, "Record 2: Initial Data2\n");
    write_record(fd, 2, "Record 3: Initial Data3\n");

    // Read and modify records
    char buffer[RECORD_SIZE + 1] = {0};

    // Access and modify the first record
    read_record(fd, 0, buffer);
    printf("Read Record 1: %s\n", buffer);
    write_record(fd, 0, "Record 1: Modified Data\n");

    // Access the second record
    read_record(fd, 1, buffer);
    printf("Read Record 2: %s\n", buffer);

    // Access and modify the third record
    read_record(fd, 2, buffer);
    printf("Read Record 3: %s\n", buffer);
    write_record(fd, 2, "Record 3: Modified Data\n");

    close(fd);
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cc 18.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Read Record 1: Record 1: Initial Data1

// Read Record 2: Record 2: Initial Data2

// Read Record 3: Record 3: Initial Data3