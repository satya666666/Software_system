/*
============================================================================
Name : 34a_server.c
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
#include <sys/wait.h>
#include <signal.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024
void handle_sigchld(int sig)                         // Signal handler to reap zombie processes created by fork()
 {
    while (waitpid(-1, NULL, WNOHANG) > 0);          // Wait for all dead processes
}
int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];
    char *response = "Hello from concurrent server";
    signal(SIGCHLD, handle_sigchld);                         // Signal handler to avoid zombie processes
    server_socket = socket(AF_INET, SOCK_STREAM, 0);          // Create a socket (IPv4, TCP)
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;                            // Server address setup
    server_addr.sin_port = htons(SERVER_PORT);                   // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY;                    // Accept any IP address

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)           // Bind the socket to the IP and port
    {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, 5) < 0)                                                           // Listen for incoming connections
    {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Concurrent server listening on port %d...\n", SERVER_PORT);
    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);            // Accept a connection from a client
        if (client_socket < 0) {
            perror("Connection accept failed");
            continue;
        }

        if (fork() == 0) {                              // Child process
            close(server_socket);                        // Close the listening socket in the child process
            int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);                // Receive data from the client
            if (bytes_received < 0) {
                perror("Failed to receive data");
            } else {
                buffer[bytes_received] = '\0';                                              // Null-terminate the received string
                printf("Message from client: %s\n", buffer);
            }
            send(client_socket, response, strlen(response), 0);                              // Send response to the client
            printf("Response sent to client.\n");
            close(client_socket);                                                            // Close the client socket and terminate the child process
            exit(0);
        }
        close(client_socket);                                                                 // Parent process: close the client socket (child process will handle communication)
    }
    close(server_socket);                                                                     // Close the server socket (this will not be reached)

    return 0;
}


// Output:

// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 34a_server.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Concurrent server listening on port 8080...
// Message from client: Hello from client
// Response sent to client.
// ^C
