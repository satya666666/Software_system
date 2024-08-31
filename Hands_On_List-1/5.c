// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.

#include <fcntl.h>   //for creat()
#include <unistd.h>  //used for sleep() and close()
#include <stdio.h>   //use for input and ouput like snprintf(), perror()
int main() {
while (1) {
for (int i = 0; i < 5; i++) {
char filename[20];                                         // name of file to be stored or created
snprintf(filename, sizeof(filename), "file%d.txt", i);     // for making the name file0.txt to file4.txt
int fd = creat(filename, 0644);                            // create the file0 to file4 with the permission 0644, owner(for read & write both),group and others(only read) 
if (fd == -1) {
perror("creat");
}
close(fd);
}
sleep(1);
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ cc 5.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// ^C
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ls
// 1a.c  1b.c  1c.c  1shell.sh  2.c  2shell.sh  3.c  4.c  5.c  a.out  fifo1  file0.txt  file1.txt  file2.txt  file3.txt  file4.txt  file_descriptor.txt  symlink1  symlink2