
#include "kernel.h"


int createServer(){
    /**
     * Create the tcp/http server running on port 6309
     */
    int socketfd;
    struct sockaddr_in server_address;

    if ((socketfd = socket(SOCKET_DOMAIN, SOCKET_TYPE, 0)) < 0){
        perror("Fail to create socket --- Terminating...");
        exit(EXIT_FAILURE);
    }
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));


    server_address.sin_family = SERVER_ADDR_NAMESPACE;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);


    if (bind(socketfd, (struct sockaddr*)&server_address, sizeof(struct sockaddr)) < 0){
        perror("Fail to bind the address to the socket --- Terminating...");
        exit(EXIT_FAILURE);
    }

    return socketfd;
}





