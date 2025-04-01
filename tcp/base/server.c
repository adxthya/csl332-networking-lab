#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
    int server_fd, client1, client2;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    // Create Socket
    server_fd = socket(AF_INET,SOCK_STREAM,0);

    // Bind socket with IP and PORT
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    printf("Server listening on %d\n", PORT);

    // Listen
    listen(server_fd,5);

    // Accept connections
    client1 = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    client2 = accept(server_fd, (struct sockaddr*)&address, &addrlen);

    while(1){
        bzero(buffer,1024);
        recv(client1, buffer, sizeof(buffer),0);
        send(client2, buffer, strlen(buffer), 0);
        printf("Client 1: %s", buffer);
        bzero(buffer,1024);
        recv(client2, buffer, sizeof(buffer),0);
        send(client1, buffer, strlen(buffer), 0);
        printf("Client 2: %s", buffer);
    }

    close(client1);
    close(client2);
    close(server_fd);
    
    return 0;
}