#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int reverse_number(int num) {
    int rev = 0;
    while (num > 0) {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return rev;
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

        if (strcmp(buffer, "exit") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        int num = atoi(buffer);
        int reversed = reverse_number(num);

        sprintf(buffer, "%d", reversed);
        send(new_socket, buffer, strlen(buffer), 0);
    }

    close(new_socket);
    close(server_fd);
}
