#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int client;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];

    // Create Socket
    client = socket(AF_INET,SOCK_STREAM,0);

    // Bind socket with IP and PORT
    address.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    address.sin_port = htons(PORT);

    // Connect to server
    connect(client, (struct sockaddr*)&address, sizeof(address));

    // Read Message
    while(1){
        printf("Enter the message: ");
        fgets(buffer, 1024, stdin);
        send(client, buffer, strlen(buffer), 0);
        recv(client, buffer, sizeof(buffer), 0);
        bzero(buffer, 1024);
    }
    
    return 0;
}