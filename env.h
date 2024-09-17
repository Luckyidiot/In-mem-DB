#pragma once

#ifdef SERVER

    #include <netinet/in.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/socket.h>

    /**
     * These MACROS are used in Server creation function.
     */
    #define PORT                    6309
    #define SOCKET_DOMAIN           AF_INET
    #define SOCKET_TYPE             SOCK_STREAM
    #define SERVER_ADDR_NAMESPACE   PF_INET
    #define MAX_PENDING_REQUESTS    50
    #define BANDWIDTH               2

#endif