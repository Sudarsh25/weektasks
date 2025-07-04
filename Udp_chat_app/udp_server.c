/*
 * SPDX-License-Identifier: MIT
 * Author: SreeSudarshan RV
 * Project: UDP Chat Server in C
 *
 * Description:
 * This program implements a simple UDP server using sockets. It receives messages
 * from a client, displays them, takes a reply from the server user, and sends it back.
 *
 * License: MIT License
 * You are free to use, modify, and distribute this code under the terms of the MIT license.
 *
 * GitHub Repository: https://github.com/Sudarsh25/weektasks/Udp_chat_app
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    // Check if port number is provided
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return -1;
    }

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Clear memory for address structures
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Set server address info
    servaddr.sin_family = AF_INET;                // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;        // Accept connections from any IP
    servaddr.sin_port = htons(atoi(argv[1]));     // Convert port string to network order

    // Bind socket to IP and port
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        return -1;
    }

    printf("Server ready. Waiting for messages...\n");

    len = sizeof(cliaddr);

    while (1) {
        // Receive message from client
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                         (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';  // Null-terminate received message

        // Print the message from client
        printf("Client: %s", buffer);

        // Get server's response from user
        printf("You (Server): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Send response back to client
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&cliaddr, len);
    }

    return 0;
}
