#include "kernel.h"
#include "utils.h"


int main(int argc, char **argv){
    
    int server = createServer();
    
    check_error(listen(server, MAX_PENDING_REQUESTS), "LISTEN:");
    printf("Listening...\n");
    
    while (1){
        printf("Waiting...\n");
        int client = accept(server, NULL, NULL);
        check_error(client, "Fail to accept new connection");
        handleClient(client);
        shutdown(client, SHUT_RD);
    }
    
    shutdown(server, SHUT_RD);
    
    return 0;
}


