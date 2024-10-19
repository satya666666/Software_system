#include<sys/socket.h>    // Provides definitions and functions for creating and using sockets (e.g., socket, connect)
#include<netinet/ip.h>    // Defines structures for handling IP addresses and protocols (e.g., sockaddr_in, AF_INET)
#include<stdio.h>         // Standard Input/Output library (e.g., printf, scanf) for reading/writing data
#include<unistd.h>        // Provides access to POSIX system calls (e.g., read, write, close)
#include<stdlib.h>        // Standard library for memory management and process control (e.g., malloc, exit)
#include<string.h>        // Functions for handling and manipulating strings (e.g., strcpy, strcmp, bzero)
#include<termios.h>       // Functions and structures to control terminal I/O (e.g., disable echo for password input)


void connectionHandler(int socketFD);  
// Handles communication between the client and server. 
// Reads data from the server and sends responses based on the client's input.

void hide_input(char *buffer, int size);  
// Used to hide user input (typically for password fields).
// Disables terminal echoing while reading the input to ensure privacy.


void main()
{
    int socketFD;  // File descriptor for the client-side socket
    int connectStatus;  // Variable to store the status of the connection attempt

    struct sockaddr_in address;  // Struct to hold the server address information
    
    // Creating a socket with IPv4 and TCP (SOCK_STREAM)
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == -1)  // If socket creation fails
    {
        perror("Error\n");  // Print error message
        exit(-1);  // Exit the program with error status
    }
    printf("!!--------------The Client side socket has been successfully created--------------------------!!\n");

    // Assign IP and Port
    address.sin_addr.s_addr = htonl(INADDR_ANY);  // Assigning any local IP address
    address.sin_family = AF_INET;  // IPv4 protocol
    address.sin_port = htons(8080);  // Port number 8080 in network byte order

    // Connecting to server
    connectStatus = connect(socketFD, (struct sockaddr *)&address, sizeof(address));
    if(connectStatus == -1)  // If connection fails
    {
        perror("Error\n");  // Print error message
        exit(-1);  // Exit the program with error status
    }

    // Handling server response after successful connection
    connectionHandler(socketFD);

    exit(0);  // Exit the program successfully
}


void connectionHandler(int socketFD)
{
    char readBuffer[4096], writeBuffer[4096], tempBuffer[4096];  // Buffers to store read/write data from/to server
    int readBytes, writeBytes;  // Variables to store the number of bytes read/written

    do
    {
        bzero(readBuffer, sizeof(readBuffer));  // Clearing the read buffer
        readBytes = read(socketFD, readBuffer, sizeof(readBuffer));  // Reading data from the server
        if(readBytes == -1)  // Error in reading data
        {
            printf("!!------------------------------Now, Client has not able to read from server----------------------------------!!\n");
        }
        else if(readBytes == 0)  // No more data to read, connection closed
        {
            printf("Closing the connection\n");
        }
        else  // Data successfully read from server
        {
            // If server asks for a password, hide input while the user types
            if (strcmp(readBuffer, "Enter password: ") == 0)
            {
                hide_input(writeBuffer, sizeof(writeBuffer));  // Hide password input for security
            }            
            else  // Otherwise, handle other server messages
            {
                bzero(writeBuffer, sizeof(writeBuffer));  // Clear the write buffer
                bzero(tempBuffer, sizeof(tempBuffer));  // Clear the temporary buffer
                
                // If the server logs out the client
                if(strcmp(readBuffer, "!!----------------------------Client has been logged out-----------------------!!\n") == 0)
                {
                    strcpy(writeBuffer, "");  // Clear write buffer
                    close(socketFD);  // Close the connection
                    return;  // Exit the function
                }
                // If the message contains a specific control character ('^')
                else if(strchr(readBuffer, '^') != NULL)
                {
                    if(strlen(readBuffer) != 1)  // If the message is more than just the control character
                    {
                        strncpy(tempBuffer, readBuffer, strlen(readBuffer) - 1);  // Copy the message excluding the control character
                        printf("%s\n", tempBuffer);  // Print the modified message
                    }
                    strcpy(writeBuffer, "");  // Clear write buffer
                }
                // If the message starts with "Loan ID:" (first 8 characters)
                else if(strcmp(strncpy(tempBuffer, readBuffer, 8), "Loan ID:") == 0)
                {
                    printf("%s\n", readBuffer);  // Print the full message
                    strcpy(writeBuffer, "");  // Clear write buffer
                }
                // Default case: the server expects an input from the client
                else
                {
                    printf("%s\n", readBuffer);  // Print the server message
                    scanf("%s", writeBuffer);  // Get user input to send to the server
                }                
            }
            
            writeBytes = write(socketFD, writeBuffer, sizeof(writeBuffer));  // Write user input to the server
            if(writeBytes == -1)  // Error in writing data
            {
                printf("!!------------------Client has not able to write into the server-------------------------!!\n");
                printf("!!-----------------Now client has to close the connection to the server---------------------!!\n");
                break;  // Exit the loop and close connection
            }
        }
    } while(readBytes > 0);  // Loop until no more data is read

    close(socketFD);  // Close the socket connection
}


// Hiding Password
void hide_input(char *buffer, int size) {
    struct termios oldt, newt;
    
    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable echoing of characters
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read input
    printf("Enter password: ");
    scanf("%s", buffer);

    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}