// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to print the following information about a given file. 
// a. inode
// b. number of hard links
// c. uid
// d. gid
// e. size
// f. block size
// g. number of blocks
// h. time of last access
// i. time of last modification
// j. time of last change

#include <sys/stat.h>               // for file information like size,  modification tme 
#include <stdio.h>
#include <time.h>                   // for manipulation time & convert time into human readable format
int main() {
struct stat fil;                   // fil is a structure of struct stat type.
if (stat("Example.txt", &fil) == -1) {
perror("stat");
return 1;
}
printf("Inode: %ld\n", (long)fil.st_ino);     // unique identifier for the file within the file system
printf("Number of Hard Links: %ld\n", (long)fil.st_nlink);    // additional directory entry for the file
printf("UID: %d\n", fil.st_uid);                              // user id of file
printf("GID: %d\n", fil.st_gid);                             // group id  of file
printf("Size: %ld bytes\n", (long)fil.st_size);
printf("Block Size: %ld bytes\n", (long)fil.st_blksize);
printf("Number of Blocks: %ld\n", (long)fil.st_blocks);
printf("Last Access Time: %s", ctime(&fil.st_atime));
printf("Last Modification Time: %s", ctime(&fil.st_mtime));
printf("Last Status Change Time: %s", ctime(&fil.st_ctime));
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 9.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// Inode: 1972301
// Number of Hard Links: 1
// UID: 1000
// GID: 1000
// Size: 147 bytes
// Block Size: 4096 bytes
// Number of Blocks: 8
// Last Access Time: Tue Aug 27 14:57:17 2024
// Last Modification Time: Wed Aug 21 12:46:54 2024
// Last Status Change Time: Tue Aug 27 13:48:04 2024