#include<stdio.h>      // for basic I/O operations like printf, scanf
#include<stdlib.h>     // for memory allocation, process control like malloc, calloc
#include<string.h>     // for string manipulation functions like strcpy, strlen, strcat
#include<time.h>       // for date and time functions like time, localtime
#include<fcntl.h>      // for file control options like open, O_RDONLY, O_WRONLY
#include<unistd.h>     // for POSIX operating system API, provides access to system calls like read, write, close, fork
#include<crypt.h>      // for encryption functions like crypt for password hashing
#include<semaphore.h>  // for POSIX semaphores, used for process synchronization
#include<netinet/ip.h> // for Internet Protocol family like sockaddr_in for network communication
#include<sys/types.h>  // for data types used in system calls like pid_t, size_t
#include<sys/socket.h> // for creating and managing network sockets like socket, bind, listen
#include<sys/stat.h>   // for handling file status information like stat, chmod, mkdir
#include<sys/sem.h>    // for System V semaphore control operations like semop, semctl
#include<sys/wait.h>   // for waiting for process termination like wait, waitpid
#include<errno.h>      // for error reporting, defines macros for error codes like errno
#include<signal.h>     // for handling signals like signal, kill

// File paths for different data files
#define EMPPATH "./Database/employees.txt"
#define CUSPATH "./Database/customers.txt"
#define LOANPATH "./Database/loanDetails.txt"
#define COUNTERPATH "./Database/loanCounter.txt"
#define HISTORYPATH "./Database/trans_hist.txt"
#define FEEDPATH "./Database/feedback.txt"
#define HASHKEY "$6$saltsalt$"

// Menus for different users
#define MAINMENU "\n!!-----------------Now you want to decide to login as:- --------------!!\n1. Admin\n2. Manager\n3. Employee\n4. Customer\n5. Exit\nEnter your choice: "
#define ADMMENU "\n!!---------------This is the admin menu(Please select from 1 to 5):- ---------------!!\n1. Add New Bank Employee\n2. Modify Customer/Employee Details\n3. Manage User Roles\n4. Change Password\n5. Add Manager\n6. Logout\nEnter your choice: "
#define CUSMENU "\n!!-----------------This is the customer menu(Please select from 1 to 10):- ----------------!!\n1. Deposit\n2. Withdraw\n3. View Balance\n4. Apply for a loan\n5. Money Transfer\n6. Change Password\n7. View Transaction\n8. Add Feedback\n9. Logout\n10. Exit\nEnter your choice: "
#define EMPMENU "\n!!----------------------This is the employee menu(Please select from 1 to 8):- ------------------------!!\n1. Add New Customer\n2. Modify Customer Details\n3. Approve/Reject Loans\n4. View Assigned Loan Applications\n5. View Customer Transactions\n6. Change Password\n7. Logout\n8. Exit\nEnter your choice: "
#define MNGMENU "\n!!------------------------This is the manager employee menu(Please select from 1 to 6):- -----------------------!!\n1. Activate/Deactivate Customer Accounts\n2. Assign Loan Application Processes to Employees\n3. Review Customer Feedback\n4. Change Password\n5. Logout\n6. Exit\nEnter your choice: "

// Function prototypes for different functionalities
void employee(int connFD);
void manager(int connFD);
void admin(int connFD);
void connectionHandler(int connFD);
void exitClient(int connFD, int id);
void cleanupSemaphore(int signum);
void setupSignalHandlers();
sem_t *initializeSemaphore(int accountNumber);
sem_t *sema;
char semName[50];

// Including necessary header files for structures and functions
#include "./DataStruct/Struct.h"
#include "./Procedure/Customer.h"
#include "./Procedure/Admin.h"
#include "./Procedure/Employee.h"
#include "./Procedure/Manager.h"

int main() {
    int socketFD, connectionFileDescriptor;
    int bindStatus;
    int listenStatus;
    int clientSize;

    struct sockaddr_in address, client; 

    // Creating a socket for communication
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFD == -1) {
        perror("Error");
        exit(-1);  // Exit if socket creation fails
    }
    printf("!!----------------Here, now the server is created Successfully---------------------!!\n");

    // Assigning IP address and port to the server
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    // Binding the socket to the IP and port
    bindStatus = bind(socketFD, (struct sockaddr *)&address, sizeof(address));
    if (bindStatus == -1) {
        perror("Error");
        exit(-1);  // Exit if binding fails
    }
    printf("!!-------------------------Here, now the socket binds to client successfully---------------------!!\n");

    // Start listening for incoming connections
    listenStatus = listen(socketFD, 2);
    if (listenStatus == -1) {
        perror("Error");
        exit(-1);  // Exit if listening fails
    }
    printf("!!---------------------------Here, the server is waiting for listening process-----------------------!!\n");

    // Accepting and handling client connections
    while(1) {
        clientSize = sizeof(client);
        connectionFileDescriptor = accept(socketFD, (struct sockaddr *) &client, &clientSize);
    
        if (connectionFileDescriptor == -1)
            perror("Error");
        else {
            // Creating a new process to handle each client
            if(fork() == 0) {
                // Child process handles the client
                connectionHandler(connectionFileDescriptor);
            }
        }
    }
    close(socketFD);  // Close socket after finishing

    return 0;
}

// Function to handle client connection
void connectionHandler(int connFD) {
    char readBuffer[4096], writeBuffer[4096];
    int readBytes, writeBytes, choice;

    // Main loop to interact with client
    while(1) {
        // Send main menu to the client
        writeBytes = write(connFD, MAINMENU, sizeof(MAINMENU));
        if(writeBytes == -1) {
            printf("!!----------Now, the client is not able to send the data----------!!\n");
        } else {   
            bzero(readBuffer, sizeof(readBuffer));  // Clear the read buffer
            readBytes = read(connFD, readBuffer, sizeof(readBuffer));  // Reading client's input
            if(readBytes == -1) {
                printf("!!----------------Not able to read the data from the client----------------!!\n");
            } else if(readBytes == 0) {
                printf("!!---------------There is no data move to the server---------------------!!\n");
            } else {
                choice = atoi(readBuffer);  // Convert client's input to an integer
                printf("Client entered: %d\n", choice);
                
                // Handling different user choices
                switch (choice) {
                    case 1:
                        admin(connFD);  // Admin login
                        break;
                    
                    case 2:
                        manager(connFD);  // Manager login
                        break;
                            
                    case 3:
                        employee(connFD);  // Employee login
                        break;

                    case 4:
                        customer(connFD);  // Customer login
                        break;

                    case 5:
                        exitClient(connFD, 0);  // Exit client
                        return;

                    default:
                        printf("!!-----------------------This is the invalid choice----------------------------!!\n");
                        break;
                }
            }
        }
    }
}

// Function to clean up semaphore on signal interruption
void cleanupSemaphore(int signum) {
    if (sema != NULL) {
        sem_post(sema);  // Release the semaphore
        sem_close(sema);  // Close the semaphore
        sem_unlink(semName);  // Remove the semaphore from the system
    }
    printf("!!----------------------------The program has been interrupted now--------------------!!\n");
    _exit(signum);  // Exit the program
}

// Function to initialize semaphore for an account
sem_t *initializeSemaphore(int id) {
    snprintf(semName, 50, "/sem_%d", id);  // Create a unique name for the semaphore
    return sem_open(semName, O_CREAT, 0644, 1);  // Initialize the semaphore to 1
}

// Function to set up signal handlers for various signals
void setupSignalHandlers() {
    signal(SIGINT, cleanupSemaphore);  // Handle interrupt signal
    signal(SIGTERM, cleanupSemaphore);  // Handle termination signal
    signal(SIGSEGV, cleanupSemaphore);  // Handle segmentation fault
    signal(SIGHUP, cleanupSemaphore);  // Handle hangup signal
    signal(SIGQUIT, cleanupSemaphore);  // Handle quit signal
}

// Function to handle client exit and clean up
void exitClient(int connFD, int id) {
    snprintf(semName, 50, "/sem_%d", id);  // Create semaphore name for the client

    sem_t *sema = sem_open(semName, 0);  // Open the semaphore
    if (sema != SEM_FAILED) {
        sem_post(sema);  // Release the semaphore
        sem_close(sema);  // Close the semaphore
        sem_unlink(semName);  // Unlink semaphore
    }

    bzero(writeBuffer, sizeof(writeBuffer));  // Clear write buffer
    strcpy(writeBuffer, "!!-----------------Now, the client is logged out...............!!\n");
    write(connFD, writeBuffer, sizeof(writeBuffer));  // Inform client about logout
    read(connFD, readBuffer, sizeof(readBuffer));  // Read any final input from client
}
