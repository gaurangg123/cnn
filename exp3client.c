#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // Assuming the server IP is 127.0.0.1 (localhost)
#define SERVER_PORT 8080       // Assuming the server listens on port 8080
#define BUFFER_SIZE 100

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &(server_addr.sin_addr));

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to the server");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Take user input for the message
        printf("Enter the message to send to SRM's server (or 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove the trailing newline character

        // Send the message to the server
        send(client_socket, message, strlen(message), 0);
        printf("Sent: %s\n", message);

        // Check if the user wants to exit
        if (strcmp(message, "exit") == 0) {
            break;
        }

        // Receive message from the server
        recv(client_socket, buffer, sizeof(buffer), 0);
        printf("Received from server: %s\n", buffer);
    }

    // Close the socket
    close(client_socket);

    return 0;
}

