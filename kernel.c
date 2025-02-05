
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


int read_req(void* raw_req, int __socket){
    /**
     * Read the request from __socket into raw_req.
     * return 1 if succeed to read, otherwise return -1
     * 
     * Use buffer because the request may be insanely long, and in which case the size
     * of raw_req needs to be expanded constantly.
     */
    char buffer[BANDWIDTH];
    memset(buffer, '\0', BANDWIDTH);
    int offset = 0;
    ssize_t nbytes = 0;
    while ((nbytes = recv(__socket, buffer, BANDWIDTH, 0)) > 0){
        raw_req = realloc(raw_req, (nbytes + offset));
        memcpy((raw_req + offset), buffer, nbytes);
        memset(buffer, '\0', BANDWIDTH);
        offset += nbytes;
    }
    if (nbytes < 0){
        perror("FAIL TO RECEIVE REQUEST:");
        return -1;
    }
    return 1;
}

int http_startline_parser(const char *raw_req, http_req *request){
    /**
     * Parse the start line of the http request only
     * 
     * 1) This function also includes checking http format.
     * 2) Pass the position of the header to headerpos, doing this can avoid re-iteration when we parse the header.
     * 
     * If it fails, it returns -1; otherwise it returns the position of the beginning of the header.
     */
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
    for (int i = 0; i < 3; i++){
        int offset = 1;
        while ( ((*(raw_req + position + offset)) != '\r') && ((*(raw_req + position + offset)) != ' ') ){
            offset++;
        }

        switch (i){
        case 0:
            // get the METHOD
            request->method = (char*)malloc(offset + 1);
            memset(request->method, '\0', offset + 1);
            strncpy(request->method, (raw_req + position), offset);
            break;
        case 1:
            // get the PATH
            request->path = (char*)malloc(offset + 1);
            memset(request->path, '\0', offset + 1);
            strncpy(request->path, (raw_req + position), offset);
            break;
        case 2:
            // get the PATH
            request->http_version = (char*)malloc(offset + 1);
            memset(request->http_version, '\0', offset + 1);
            strncpy(request->http_version, (raw_req + position), offset);
            break;
        default:
            break;
        }
        position += (offset + 1);
    }

    position++;
    return position;
}

int http_headers_parser(const char* raw_req, int header_pos, http_header* header){
    /**
     * PARSING HEADER
     * Due to the format of the header
     *      header: val
     * We will iterate twice to retrieve the header and the value.
     * This function can only parse one line of header at a time.
     * 
     * If it reaches to the end of the header part, it will return -1.
     * Otherwise it will return the position of the next line of header.
     */

    if (*(raw_req + header_pos) == '\r'){
        return -1;
    }
    int offset = 1;
    while (*(raw_req + header_pos + offset) != ':'){
        offset++;
    }
    header->head = (char*)malloc(offset + 1);
    memset(header->head, '\0', offset + 1);
    strncpy(header->head, (raw_req + header_pos), offset);

    header_pos += (offset + 2);
    offset = 1;
    while (*(raw_req + header_pos + offset) != '\r'){
        offset++;
    }
    header->val = (char*)malloc(offset + 1);
    memset(header->val, '\0', offset + 1);
    strncpy(header->val, (raw_req + header_pos), offset);

    header_pos += (offset + 2);
    return header_pos;
}

int handleClient(int __socket){
    /**
     * 1) Read the request in raw string
     * 2) Parse it to get METHOD, PATH, HTTP_VERSION, HEADERS
     * 3) Pass those data to python script
     * 
     * If it fails, return -1; otherwise, if succeed, return 1
     */

    // Read the request in the raw string format
    char *raw_req = (char*)malloc(1);
    if (read_req(raw_req, __socket) == -1){
        return -1;
    }

    /**
     * Parse the raw request.
     * This involves:
     *      1) Get the first line of the request
     *      2) Get the headers
     * 
     * Due to the differences in the structure of the first line and the rest of the request, we have to separate them into 
     * two steps.
     */
    //Parse the start line
    http_req request;
    int header_pos = 0;
    if ((header_pos = http_startline_parser(raw_req, &request)) == -1){
        fprintf(stderr, "Fail to parse the request\n");
        return -1;
    }
    //Parse the headers
    http_header headers[50];
    for (int i = 0; i < 50; i++){
        //The header_pos will be updated constantly.
        header_pos = http_headers_parser(raw_req, header_pos, &headers[i]);
        if (header_pos == -1){
            break;
        }
    }

    /**
     * Handling the request :: Call Python script and pass the request and headers into it.
     */
    

    free(request.method);
    free(request.path);
    free(request.http_version);
    free(raw_req);
    return 0;
}


