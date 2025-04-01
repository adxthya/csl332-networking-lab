#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in addr;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    while (1) {
        printf("Enter a number (or 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline

        send(sock, buffer, strlen(buffer), 0);
        if (strcmp(buffer, "exit") == 0) break;

        bzero(buffer, sizeof(buffer));
        read(sock, buffer, sizeof(buffer));

        printf("Reversed: %s\n", buffer);
    }

    close(sock);
}
