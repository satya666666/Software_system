/*
============================================================================
Name : 34b_server.c
Author : Satyam Gupta
Description : Write a program to create a concurrent server.
b. use pthread_create
Date: 19th Sept. 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024
void* handle_client(void* client_socket_ptr)                                  // Function to handle client communication (this runs in a separate thread)
{
    int client_socket = *((int*)client_socket_ptr);
    free(client_socket_ptr);                                                      // Free the memory allocated for client_socket_ptr
    char buffer[BUFFER_SIZE];
    char *response = "Hello from concurrent server using pthread";
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);                 // Receive data from the client
    if (bytes_received < 0) {
        perror("Failed to receive data");
        close(client_socket);
        pthread_exit(NULL);
    }

    buffer[bytes_received] = '\0';                                                    // Null-terminate the received string
    printf("Message from client: %s\n", buffer);
    send(client_socket, response, strlen(response), 0);                               // Send response to the client
    printf("Response sent to client.\n");
    close(client_socket);                                                             // Close the client socket
    pthread_exit(NULL);
}
int main() {
    int server_socket, *client_socket_ptr;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    pthread_t thread_id;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);                                                 // Create a socket (IPv4, TCP)
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    // Server address setup
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);                                                     // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY;                                                      // Accept any IP address
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)              // Bind the socket to the IP and port
    {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, 5) < 0)                                                      // Listen for incoming connections
    {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Concurrent server using pthread listening on port %d...\n", SERVER_PORT);
    while (1) {
        addr_size = sizeof(client_addr);
        // Accept a connection from a client
        client_socket_ptr = malloc(sizeof(int));                                           // Allocate memory for client socket
        *client_socket_ptr = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        if (*client_socket_ptr < 0) {
            perror("Connection accept failed");
            free(client_socket_ptr);                                                     // Free memory in case of failure
            continue;
        }
        if (pthread_create(&thread_id, NULL, handle_client, client_socket_ptr) != 0)    // Create a thread to handle the client
        {
            perror("Failed to create thread");
            free(client_socket_ptr);                        // Free memory in case of failure
            continue;
        }
        pthread_detach(thread_id);                        // Detach the thread so that it cleans up after itself when done
    }
    close(server_socket);                                // Close the server socket (this will not be reached)
    return 0;
}




// Output:


// satyam@satyam-X542UQ:~/Desktop/ss_list2$ cc 34b_server.c
// satyam@satyam-X542UQ:~/Desktop/ss_list2$ ./a.out
// Concurrent server using pthread listening on port 8080...
// Message from client: Hello from client
// Response sent to client.
// ^C

