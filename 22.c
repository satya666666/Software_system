// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
int fd = open("file.txt", O_RDWR | O_CREAT, 0644);
if (fd == -1) {
perror("open");
return 1;
}
pid_t pid = fork();
if (pid == -1) {
perror("fork");
close(fd);
return 1;
} else if (pid == 0) {
write(fd, "Child writes\n", 13);
} else {
write(fd, "Parent writes\n", 14);
}
close(fd);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 22.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cat file.txt
// Parent writes
// Child writes

