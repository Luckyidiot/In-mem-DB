#include "kernel.h"
#include "utils.h"

int main(void){
    
    int server = createServer();
    
    check_error(listen(server, MAX_PENDING_REQUESTS), "LISTEN:");
    printf("Listening...\n");
    
    http request;
    while (1){
        printf("Waiting...\n");
        int client = accept(server, NULL, NULL);
        check_error(client, "Fail to accept new connection");
        
        char* raw_req;
        //http request;
        read_req(raw_req, client);
        
        //httpParser(raw_req, NULL);
        
        printf("%s\n", raw_req);
        /*
        printf("METHOD is %s\n", request.method);
        printf("PATH is %s\n", request.path);
        printf("HTTP version is %s\n", request.http_version);

        free(request.method);
        free(request.path);
        free(request.http_version);
        */
        shutdown(client, SHUT_RD);
    }
    
    shutdown(server, SHUT_RD);
    return 0;
}