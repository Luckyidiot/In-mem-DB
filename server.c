#include "kernel.h"
#include "utils.h"

int main(int argc, char** argv){
    

    
    int server = createServer();
    
    check_error(listen(server, MAX_PENDING_REQUESTS), "LISTEN:");
    printf("Listening...\n");
    
    while (1){
        printf("Waiting...\n");
        int client = accept(server, NULL, NULL);
        check_error(client, "Fail to accept new connection");
        
        char* buffer;
        struct req_comp request;

        getRequest(buffer, client);
        int parser_status = httpParser(buffer, &request);
        
        /*
        printf("METHOD is %s\n", request.method);
        printf("PATH is %s\n", request.path);
        printf("HTTP version is %s\n", request.http_version);

        free(request.method);
        free(request.path);
        free(request.http_version);
        */
    }
    
    
    return 0;
}