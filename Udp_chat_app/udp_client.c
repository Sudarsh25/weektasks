/*
 * SPDX-License-Identifier: MIT
 * Author: Sree Sudarshan RV
 * Project: UDP Chat Client in C
 *
 * Description:
 * This code implements a UDP client in C that allows a user to send messages
 * to a server and receive responses. It uses sockets and command-line arguments
 * for IP and port configuration.
 *
 * License: MIT License
 * You are free to use, modify, and distribute this code under the terms of the MIT license.
 *
 * GitHub Repository: https://github.com/Sudarsh25/udp-chat-app
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr;

    // Check if IP and port are provided in command line
    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        return -1;
    }

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Setup server address structure
    servaddr.sin_family = AF_INET;                 // Use IPv4
    servaddr.sin_port = htons(atoi(argv[2]));      // Convert port to network byte order
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr); // Convert IP string to binary form

    while (1) {
        // Read message from user
        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);

        // Send message to server
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&servaddr, sizeof(servaddr));

        // Receive reply from server
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        buffer[n] = '\0';  // Null-terminate the received message

        // Display server's reply
        printf("Server: %s\n", buffer);
    }

    return 0;
}
