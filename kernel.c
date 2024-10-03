
#include "kernel.h"


int createServer(){
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


void getRequest(void* __buff, int __socket){
    int index = 0;
    ssize_t nbytes = 0;

    while ((nbytes = recv(__socket, (__buff + index), BANDWIDTH, 0)) > 0){
        index += nbytes;
    }
}

int httpParser(const char* __req){
    
    /**
     * Confirm the http protocol using regex.
     * Perhaps there should be another mechanics.
     */
    regex_t http_regex;

    if (regcomp(&http_regex, HTTP_REGEX, REG_EXTENDED) != 0){
        fprintf(stderr, "Fail to compile regex for http request pattern --- Terminating\n");
        exit(EXIT_FAILURE);
    }
    if (regexec(&http_regex, __req, 0, NULL, REG_NOTEOL) != 0){
        return -1;
    }

    /* PARSING

        Http requests' lines are ended with \r\n

        Because the structure of the first line and the rest is not the same:
        Step 1: Parse the first line for Method, URL, and HTTP version
            - The char *metadata[3] has 3 elements because we need to get 3 pieces of info from the first line: METHOD /PATH HTTP_VERSION
        Step 2: Parse the headers
     */
    int position = 0;
    int index = 0;
    char *metadata[3];
    while ( ((*(__req + position)) != '\r') && ((*(__req + position)) != '\n') ){
        // Parse the first line
        int offset = 1;
        while ( ((*(__req + position + offset)) != '\r') && ((*(__req + position + offset)) != ' ') ){
            offset++;
        }

        metadata[index] = (char*)malloc(offset + 1);
        memset(metadata[index], '\0', offset + 1);
        strncpy(metadata[index], (__req + position), offset);
        position += (offset + 1);
        index++;
    }
    
    printf("METHOD is %s\n", metadata[0]);
    printf("PATH is %s\n", metadata[1]);
    printf("HTTP VERSION is %s\n", metadata[2]);
    free(metadata[0]);
    free(metadata[1]);
    free(metadata[2]);
    // Parse the headers
    /*
    while (1){
        int offset = 1;

        for (; ((*(char*)(__req + position)) == "\n"); position++);
        position++;

        while ((*(char*)(__req + position + offset)) != ":"){
            offset++;
        }
        // Read the header
        
        
    }
    */
    
    return 0;
    
}




