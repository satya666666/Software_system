/*
============================================================================
Name : 34a_client.c
Author : Satyam Gupta
Description : Write a program to create a concurrent server.
a. use fork
Date: 19th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024
int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char *message = "Hello from client";
    client_socket = socket(AF_INET, SOCK_STREAM, 0);            // Create a socket (IPv4, TCP)
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;                                // Server address setup
    server_addr.sin_port = htons(SERVER_PORT);                       // Server port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");            //  Server IP (localhost)
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)                    // Connect to the server
    {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server.\n");
    send(client_socket, message, strlen(message), 0);                        // Send a message to the server
    printf("Message sent: %s\n", message);
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);        // Receive response from the server
    if (bytes_received < 0) {
        perror("Failed to receive data");
    } else {
        buffer[bytes_received] = '\0';                                       // Null-terminate the received string
        printf("Server response: %s\n", buffer);
    }
    close(client_socket);
    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 34a_client.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Connected to the server.
// Message sent: Hello from client
// Server response: Hello from concurrent server


