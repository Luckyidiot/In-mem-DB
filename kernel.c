
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


void read_req(void* __buff, int __socket){
    int index = 0;
    ssize_t nbytes = 0;

    while ((nbytes = recv(__socket, (__buff + index), BANDWIDTH, 0)) > 0){
        index += nbytes;
    }
}

int httpParser(const char *__req){
    
    /**
     * Confirm the http protocol using regex.
     * 
     * Cannot put http_regex outside and pass into this func => Segmentation fault
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
    
    free(metadata[0]);
    free(metadata[1]);
    free(metadata[2]);
    //request->method = metadata[0];
    //request->path = metadata[1];
    //request->http_version = metadata[2];

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


int handleClient(int __socket){
    printf("Handling client request\n");
    char *raw_req;
    /**
     * 1) Read the request in raw string
     * 2) Parse it to get METHOD, PATH, HTTP_VERSION, HEADERS
     * 3) Pass those data to python script
     */

    // Read the request in the raw string format
    printf("Check point 0");
    int index = 0;
    printf("Check point 1");
    ssize_t nbytes = 0;
    printf("Check point 2");
    while ((nbytes = recv(__socket, (raw_req + index), BANDWIDTH, 0)) > 0){
        index += nbytes;
        printf("Read request\n");
    }

    printf("%s\n", raw_req);
    /**
     * Parse the raw request.
     * This involves:
     *      1) Check if this is http request using regex
     *      2) Get the first line of the request
     *      3) Get the headers
     * 
     * Due to the differences in the structure of the first line and the rest of the request, we have to separate them into 
     * two steps.
     */
    // HTTP format check
    regex_t http_regex;
    if (regcomp(&http_regex, HTTP_REGEX, REG_EXTENDED) != 0){
        fprintf(stderr, "Fail to compile regex for http request pattern --- Terminating\n");
        exit(EXIT_FAILURE);
    }
    if (regexec(&http_regex, raw_req, 0, NULL, REG_NOTEOL) != 0){
        fprintf(stderr, "This is not http request --- Terminating\n");
        return -1;
    }

    // Get the first line
    int position = 0;
    char *metadata[3];

    for (int i = 0; i < 3; i++){
        int offset = 1;
        while ( ((*(raw_req + position + offset)) != '\r') && ((*(raw_req + position + offset)) != ' ') ){
            offset++;
        }

        metadata[i] = (char*)malloc(offset + 1);
        memset(metadata[i], '\0', offset + 1);
        strncpy(metadata[i], (raw_req + position), offset);

        position += (offset + 1);
    }
    position++;

    printf("METHOD is %s\n", metadata[0]);
    printf("PATH is %s\n", metadata[1]);
    printf("HTTP version is %s\n", metadata[2]);

    free(metadata[0]);
    free(metadata[1]);
    free(metadata[2]);

    return 0;
    /*
    while ( ((*(raw_req + position)) != '\r') && ((*(raw_req + position)) != '\n') ){
        int offset = 1;
        while ( ((*(raw_req + position + offset)) != '\r') && ((*(raw_req + position + offset)) != ' ') ){
            offset++;
        }

        metadata[index] = (char*)malloc(offset + 1);
        memset(metadata[index], '\0', offset + 1);
        strncpy(metadata[index], (raw_req + position), offset);

        position += (offset + 1);
        index++;
    }
    */

}


