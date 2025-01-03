#pragma once

#ifdef SERVER
    
    #include <stdlib.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    

    /**
     * These MACROS are used in Server creation function.
     */
    #define PORT                    6309
    #define SOCKET_DOMAIN           AF_INET
    #define SOCKET_TYPE             SOCK_STREAM
    #define SERVER_ADDR_NAMESPACE   PF_INET
    #define MAX_PENDING_REQUESTS    50
    #define BANDWIDTH               256
    
    #define HTTP_REGEX              "^(GET|POST|PUT|PATCH|DELETE|HEAD|OPTIONS|CONNECT) /.* (HTTP|HTTPS)/1\\.[01]\r\n.*"
    // fam://username@localhost:port/dbnumber/password/command?[attribute]=[value]
    #define FAM_REGEX               "fam://(.*)@(localhost):([1-9][0-9]*)/(.*)/(.*)/(.+)\\?(.*)"
#endif