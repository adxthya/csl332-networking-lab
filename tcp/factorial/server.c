#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int factorial(int num) {
    int fact = 1;
    for (int i = 2; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    printf("Server listening on port %d...\n", PORT);

    new_socket = accept(server_fd, (struct sockaddr*)&addr, &addrlen);
    printf("Client connected.\n");

    while (1) {
        bzero(buffer, sizeof(buffer));
        read(new_socket, buffer, sizeof(buffer));

        int num = atoi(buffer);
        int fact = factorial(num);

        sprintf(buffer, "%d", fact);
        send(new_socket, buffer, strlen(buffer), 0);
    }

    close(new_socket);
    close(server_fd);
}
