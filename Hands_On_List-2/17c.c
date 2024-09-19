/*
============================================================================
Name : 17c.c
Author : Satyam Gupta
Description : Write a program to execute ls -l | wc.
c. use fcntl
Date: 11th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    int pipefd[2];
    pid_t pid1, pid2;
    if (pipe(pipefd) == -1)                    // Create a pipe
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if ((pid1 = fork()) == -1)             // Fork the first child process for 'ls -l'
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {                                      // Child process for 'ls -l'
        close(pipefd[0]);                                // Close unused read end
        fcntl(pipefd[1], F_DUPFD, STDOUT_FILENO);        // Duplicate write end to STDOUT
        close(pipefd[1]);                                // Close original write end
        execlp("ls", "ls", "-l", NULL);                  // Execute 'ls -l'
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }
    // Fork the second child process for 'wc'
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0) {                                             // Child process for 'wc'
        close(pipefd[1]);                                        // Close unused write end
        fcntl(pipefd[0], F_DUPFD, STDIN_FILENO);                  // Duplicate read end to STDIN
        close(pipefd[0]);                                        // Close original read end
        execlp("wc", "wc", NULL);                                // Execute 'wc'
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }
    close(pipefd[0]);                                      // Parent process closes both ends of the pipe and waits for children
    close(pipefd[1]);
    wait(NULL);                                            // Wait for first child
    wait(NULL);                                           // Wait for second child
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 17c.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// total 224
// -rw-rw-r-- 1 satyam satyam  1443 Sep 18 22:20 10a.c
// -rw-rw-r-- 1 satyam satyam  1589 Sep 18 22:20 10b.c
// -rw-rw-r-- 1 satyam satyam  1486 Sep 18 22:22 10c.c
// -rw-rw-r-- 1 satyam satyam  1159 Sep 18 22:24 11.c
// -rw-rw-r-- 1 satyam satyam  1142 Sep 18 22:27 12.c
// -rw-rw-r-- 1 satyam satyam   857 Sep 18 22:50 13a.c
// -rw-rw-r-- 1 satyam satyam   835 Sep 18 22:50 13b.c
// -rw-rw-r-- 1 satyam satyam   875 Sep 18 22:51 14.c
// -rw-rw-r-- 1 satyam satyam   844 Sep 18 22:52 15.c
// -rw-rw-r-- 1 satyam satyam  1013 Sep 18 22:53 16.c
// -rw-rw-r-- 1 satyam satyam  5034 Sep 18 23:28 17a.c
// -rw-rw-r-- 1 satyam satyam  2369 Sep 19 00:51 17b.c
// -rw-rw-r-- 1 satyam satyam  2222 Sep 19 00:51 17c.c
// -rw-rw-r-- 1 satyam satyam  1011 Sep 12 21:58 18.c
// -rw-rw-r-- 1 satyam satyam   639 Sep 12 21:58 19.c
// -rw-rw-r-- 1 satyam satyam  1281 Sep 18 14:57 1a.c
// -rw-rw-r-- 1 satyam satyam  1577 Sep 18 15:12 1b.c
// -rw-rw-r-- 1 satyam satyam  1509 Sep 18 15:21 1c.c
// -rw-rw-r-- 1 satyam satyam   498 Sep 12 21:58 20a.c
// -rw-rw-r-- 1 satyam satyam   540 Sep 12 21:58 20b.c
// -rw-rw-r-- 1 satyam satyam   630 Sep 12 21:59 21a.c
// -rw-rw-r-- 1 satyam satyam   629 Sep 12 21:59 21b.c
// -rw-rw-r-- 1 satyam satyam   873 Sep 12 21:59 22.c
// -rw-rw-r-- 1 satyam satyam  1744 Sep 12 21:59 23.c
// -rw-rw-r-- 1 satyam satyam   679 Sep 12 21:59 24.c
// -rw-rw-r-- 1 satyam satyam  1593 Sep 12 21:59 25.c
// -rw-rw-r-- 1 satyam satyam   871 Sep 12 21:59 26.c
// -rw-rw-r-- 1 satyam satyam   800 Sep 12 22:00 27a.c
// -rw-rw-r-- 1 satyam satyam   341 Sep 12 22:00 27b.c
// -rw-rw-r-- 1 satyam satyam   808 Sep 12 22:00 28.c
// -rw-rw-r-- 1 satyam satyam   648 Sep 12 22:00 29.c
// -rw-rw-r-- 1 satyam satyam  1342 Sep 18 15:32 2.c
// -rw-rw-r-- 1 satyam satyam  1199 Sep 12 22:00 30.c
// -rw-rw-r-- 1 satyam satyam  1022 Sep 12 22:01 31.c
// -rw-rw-r-- 1 satyam satyam  1475 Sep 12 22:01 32.c
// -rw-rw-r-- 1 satyam satyam  1607 Sep 12 22:01 33.c
// -rw-rw-r-- 1 satyam satyam  1693 Sep 12 22:02 34a.c
// -rw-rw-r-- 1 satyam satyam  2450 Sep 12 22:02 34b.c
// -rw-rw-r-- 1 satyam satyam   901 Sep 18 15:35 3.c
// -rw-rw-r-- 1 satyam satyam  1467 Sep 18 16:43 4.c
// -rw-rw-r-- 1 satyam satyam  1610 Sep 18 16:45 5.c
// -rw-rw-r-- 1 satyam satyam  1207 Sep 18 17:03 6.c
// -rw-rw-r-- 1 satyam satyam  1131 Sep 18 17:10 7.c
// -rw-rw-r-- 1 satyam satyam  1129 Sep 18 17:20 8a.c
// -rw-rw-r-- 1 satyam satyam  1234 Sep 18 18:03 8b.c
// -rw-rw-r-- 1 satyam satyam  1079 Sep 18 18:54 8c.c
// -rw-rw-r-- 1 satyam satyam  1223 Sep 18 18:59 8d.c
// -rw-rw-r-- 1 satyam satyam  1607 Sep 18 21:35 8e.c
// -rw-rw-r-- 1 satyam satyam  1726 Sep 18 21:56 8f.c
// -rw-rw-r-- 1 satyam satyam  1799 Sep 18 22:02 8g.c
// -rw-rw-r-- 1 satyam satyam  1100 Sep 18 22:04 9.c
// -rwxrwxr-x 1 satyam satyam 16304 Sep 19 00:51 a.out
// prw-rw-r-- 1 satyam satyam     0 Sep 12 19:56 fifo_mkfifo
// prw-rw-r-- 1 satyam satyam     0 Sep 12 19:56 fifo_mknod
// ^C