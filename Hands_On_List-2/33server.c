/*
============================================================================
Name : 33server.c
Author : Satyam Gupta
Description : Write a program to communicate between two machines using socket.
b.) server
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
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    char *response = "Hello from server";
    server_socket = socket(AF_INET, SOCK_STREAM, 0);                                           // Create a socket (IPv4, TCP)
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;                                                        // Server address setup
    server_addr.sin_port = htons(SERVER_PORT);                                               // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY;                                                // Accept any IP address
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)         // Bind the socket to the IP and port
    {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, 5) < 0)                                                        // Listen for incoming connections            
    {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", SERVER_PORT);
    addr_size = sizeof(client_addr);                                           // Accept a connection from a client
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
    if (client_socket < 0) {
        perror("Connection accept failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Client connected.\n");
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);              // Receive data from the client      
    if (bytes_received < 0) {
        perror("Failed to receive data");
    } else {
        buffer[bytes_received] = '\0';                                              // Null-terminate the received string
        printf("Message from client: %s\n", buffer);
    }
    send(client_socket, response, strlen(response), 0);                     // Send response to the client
    printf("Response sent: %s\n", response);
    close(client_socket);                                                   // Close the sockets
    close(server_socket);

    return 0;
}


//Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 33server.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Server listening on port 8080...
// Client connected.
// Message from client: Hello from client
// Response sent: Hello from server

