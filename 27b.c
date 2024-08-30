// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to execute ls -Rl by the following system calls 
// b. execlp

#include <unistd.h>
int main() {
execlp("ls", "ls", "-Rl", (char *)NULL);
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 27b.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// total 216
// -rw-rw-r-- 1 satyam satyam  1269 Aug 29 21:26 10.c
// -rw-rw-r-- 1 satyam satyam  2509 Aug 29 19:46 11.c
// -rw-rw-r-- 1 satyam satyam  1104 Aug 29 19:46 12.c
// -rw-rw-r-- 1 satyam satyam  1621 Aug 29 19:46 13.c
// -rw-rw-r-- 1 satyam satyam  1741 Aug 29 19:46 14.c
// -rw-rw-r-- 1 satyam satyam  1002 Aug 29 19:46 15.c
// -rw-rw-r-- 1 satyam satyam   683 Aug 30 11:18 16a.c
// -rw-rw-r-- 1 satyam satyam   525 Aug 29 21:38 16b.c
// -rw-rw-r-- 1 satyam satyam  1051 Aug 30 00:30 17a.c
// -rw-rw-r-- 1 satyam satyam  1236 Aug 30 00:33 17b.c
// -rw-rw-r-- 1 satyam satyam   640 Aug 30 00:38 18a.c
// -rw-rw-r-- 1 satyam satyam   414 Aug 29 06:55 18b.c
// -rw-rw-r-- 1 satyam satyam   709 Aug 30 00:40 19.c
// -rw-rw-r-- 1 satyam satyam  1044 Aug 22 11:34 1a.c
// -rw-rw-r-- 1 satyam satyam  1115 Aug 23 09:21 1b.c
// -rw-rw-r-- 1 satyam satyam   831 Aug 23 09:21 1c.c
// -rw-rw-r-- 1 satyam satyam   232 Aug 23 09:21 1shell.sh
// -rw-rw-r-- 1 satyam satyam   723 Aug 30 00:46 20.c
// -rw-rw-r-- 1 satyam satyam   545 Aug 30 00:47 21.c
// -rw-rw-r-- 1 satyam satyam   812 Aug 30 00:50 22.c
// -rw-rw-r-- 1 satyam satyam   686 Aug 30 00:54 23.c
// -rw-rw-r-- 1 satyam satyam   648 Aug 30 00:55 24.c
// -rw-rw-r-- 1 satyam satyam   804 Aug 30 00:57 25.c
// -rw-rw-r-- 1 satyam satyam   363 Aug 30 11:16 26b.c
// -rw-rw-r-- 1 satyam satyam  3603 Aug 30 11:15 26.c
// -rw-rw-r-- 1 satyam satyam  3733 Aug 30 12:04 27a.c
// -rw-rw-r-- 1 satyam satyam   230 Aug 30 12:04 27b.c
// -rw-rw-r-- 1 satyam satyam   241 Aug 30 11:59 27c.c
// -rw-rw-r-- 1 satyam satyam   248 Aug 30 11:59 27d.c
// -rw-rw-r-- 1 satyam satyam   245 Aug 30 12:00 27e.c
// -rw-rw-r-- 1 satyam satyam   562 Aug 30 11:17 28.c
// -rwxrwxr-x 1 satyam satyam 16288 Aug 30 10:20 29
// -rw-rw-r-- 1 satyam satyam  1013 Aug 30 11:17 29.c
// -rw-rw-r-- 1 satyam satyam   535 Aug 23 09:21 2.c
// -rw-rw-r-- 1 satyam satyam   250 Aug 23 09:21 2shell.sh
// -rw-rw-r-- 1 satyam satyam   776 Aug 30 11:17 30.c
// -rw-rw-r-- 1 satyam satyam  1287 Aug 23 09:21 3.c
// -rw-rw-r-- 1 satyam satyam   770 Aug 23 09:21 4.c
// -rw-rw-r-- 1 satyam satyam  1249 Aug 22 11:50 5.c
// -rw-rw-r-- 1 satyam satyam   976 Aug 27 12:28 6.c
// -rw-rw-r-- 1 satyam satyam  1657 Aug 27 15:30 7.c
// -rw-rw-r-- 1 satyam satyam  1084 Aug 29 21:18 8.c
// -rw-rw-r-- 1 satyam satyam  1843 Aug 27 18:03 9.c
// -rwxrwxr-x 1 satyam satyam 15960 Aug 30 12:05 a.out
// -rw-r--r-- 1 satyam satyam     0 Aug 29 21:38 example.txt
// -rw-rw-r-- 1 satyam satyam   147 Aug 21 12:46 Example.txt
// -rw-r--r-- 1 satyam satyam    27 Aug 30 00:50 file.txt
// -rw-r--r-- 1 satyam satyam     0 Aug 30 00:35 records.txt
// drwxrwxr-x 3 satyam satyam  4096 Aug 29 20:58 Software_system
// -rw-r--r-- 1 satyam satyam    10 Aug 30 00:31 tickets..txt

// ./Software_system:
// total 52
// -rw-rw-r-- 1 satyam satyam 1044 Aug 29 20:58 1a.c
// -rw-rw-r-- 1 satyam satyam 1116 Aug 29 20:58 1b.c
// -rw-rw-r-- 1 satyam satyam  829 Aug 29 20:58 1c.c
// -rw-rw-r-- 1 satyam satyam  189 Aug 29 20:58 1shell.sh
// -rw-rw-r-- 1 satyam satyam  492 Aug 29 20:58 2.c
// -rw-rw-r-- 1 satyam satyam  207 Aug 29 20:58 2shell.sh
// -rw-rw-r-- 1 satyam satyam 1244 Aug 29 20:58 3.c
// -rw-rw-r-- 1 satyam satyam  726 Aug 29 20:58 4.c
// -rw-rw-r-- 1 satyam satyam 1249 Aug 29 20:58 5.c
// -rw-rw-r-- 1 satyam satyam  976 Aug 29 20:58 6.c
// -rw-rw-r-- 1 satyam satyam 1657 Aug 29 20:58 7.c
// -rw-rw-r-- 1 satyam satyam 1085 Aug 29 20:58 8.c
// -rw-rw-r-- 1 satyam satyam 1843 Aug 29 20:58 9.c