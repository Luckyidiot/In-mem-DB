#pragma once
#define SERVER
#include "../env.h"
#include "request.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <iostream>
#include <cstring>

class Server{
    private:
        int server_socket;
        sockaddr_in server_address;
        fd_set readFDs;
        
        /**
         * CONNECTION METHODS
         */
        void accept_connection(int& maxFD);
        void close_connection(int& maxFD, int fd);
        void handle_connection(std::string raw_request, int socketFD);
        
        /**
         * NECESSITIES
         */
        std::string read_socket(int socketFD);
        bool auth(std::string username, std::string password);
        void invalid_format_response(int socketFD);
    public:
        Server();
        
        void run();
        
};