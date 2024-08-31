// Name - Satyam Gupta, Roll no.- MT2024134
// Question: Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select).

#include <sys/select.h>            // for select() and struct timeval
#include <unistd.h>
#include <stdio.h>
int main() {
fd_set read_fds;                         // hold the set of file descriptors that want to monitor for readability
struct timeval timeout;                 // timeout variable of type struct timeval, which is used to specify the maximum time select() should wait for an event.
FD_ZERO(&read_fds);                     // read_fds to be empty
FD_SET(STDIN_FILENO, &read_fds);       // set standard input file to read_fds & want to monitor standard input for readability
timeout.tv_sec = 10;                   //  select() function will wait for up to 10 seconds.
timeout.tv_usec = 0;                  // after 10 seconds and the select() function will not wait any microseconds

// ret variable stores the return value of select() & into that 3rd NULL for writability & 4th NULL for exceptional conditions, 5th just like timeout for 10 seconds
int ret = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);
if (ret == -1) {
perror("select");
} else if (ret == 0)
{
printf("No data available within 10 seconds.\n");
} else {
printf("Data is available.\n");
}
return 0;
}

// Output:

// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ gcc 13.c
// satyam@satyam-X542UQ:~/Desktop/Software_system-File$ ./a.out
// No data available within 10 seconds.
