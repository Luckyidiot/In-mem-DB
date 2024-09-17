#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc, char** argv){
    /**
     * Client will have to produce the binary file, and then send them to
     * the server.
     * 
     * 
     * ./client 127.0.0.1
    */

    int socketfd;
    struct sockaddr_in server_address;


    if ((socketfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror("Fail to create socket --- Terminating...");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6309);
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) < 0){
        printf("inet_pton() error for %s\n", "127.0.0.1");
        exit(EXIT_FAILURE);
    }
    
    if (connect(socketfd, (struct sockaddr*)&server_address, sizeof(struct sockaddr))< 0){
        perror("Fail to connect to server:");
        exit(EXIT_FAILURE);

    }

    char* message = "Fuck you Q";
    if (send(socketfd, message, (strlen(message) + 1), 0) < 0){
        perror("WRITE: ");
        exit(EXIT_FAILURE);
    }

    shutdown(socketfd, 0);
    return 0;

}