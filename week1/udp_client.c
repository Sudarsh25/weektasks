#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr;

    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    while (1) {
        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);

        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&servaddr, sizeof(servaddr));

        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
    }
    return 0;
}

