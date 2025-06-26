#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(atoi(argv[1]));

    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    len = sizeof(cliaddr);

    while (1) {
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                         (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);
        sendto(sockfd, buffer, n, 0, (struct sockaddr *)&cliaddr, len);
    }
    return 0;
}

