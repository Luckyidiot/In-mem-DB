#include "server.h"

Server::Server(){
    
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0){
        perror("Fail to create socket --- Terminating...");
        exit(EXIT_FAILURE);
    }
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0){
        perror("Fail to set the socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    server_address.sin_family = PF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);
    
    if (bind(server_socket, (sockaddr*)&server_address, sizeof(sockaddr)) < 0){
        perror("Fail to bind the address to the socket --- Terminating...");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
}

std::string Server::read_socket(int socketFD){
    size_t received_bytes = 0;
    std::string read_data = "";
    char buffer[BANDWIDTH];
    memset(buffer, '\0', BANDWIDTH);
    while (recv(socketFD, buffer, BANDWIDTH, 0) > 0){
        read_data += buffer;
        memset(buffer, '\0', BANDWIDTH);
    }
    
    return read_data;
}

void Server::invalid_format_response(int socketFD){
    if (send(socketFD, INVALID_REQ_MSG, strlen(INVALID_REQ_MSG), 0) < 0){
        perror("SEND FAILED");
        exit(EXIT_FAILURE);
    }
}

void Server::accept_connection(int& maxFD){
    int client_socket;
    if ((client_socket = accept(server_socket, NULL, NULL)) < 0){
        perror("ACCEPT FAILED");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    FD_SET(client_socket, &readFDs);
    if (client_socket > maxFD){
        maxFD = client_socket;
    }
}

void Server::close_connection(int& maxFD, int fd){
    close(fd);
    FD_CLR(fd, &readFDs);
    if (fd == maxFD){
        while (FD_ISSET(maxFD, &readFDs) == 0){
            maxFD --;
        }
    }
}


void Server::handle_connection(std::string raw_request, int socketFD){
    if (!Request::is_valid_format(raw_request)){
        // Invalid request's format
        invalid_format_response(socketFD);
        return;
    }
    
    std::cout << "HANDLED" << std::endl;
    
}

void Server::run(){
    if (listen(server_socket, MAX_PENDING_REQUESTS) < 0){
        perror("LISTEN FAILS");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    std::cout << "Listening..." << std::endl;
    fd_set bufferFDs;
    int maxFD = server_socket;
    
    FD_ZERO(&readFDs);
    FD_SET(server_socket, &readFDs);
    
    while (true){
        bufferFDs = readFDs;
        if (select(maxFD + 1, &bufferFDs, NULL, NULL, NULL) < 0){
            perror("SELECT ERROR");
            close(server_socket);
            exit(EXIT_FAILURE);
        }
        int bufferMax = maxFD;
        for (int fd = 0; fd < bufferMax; fd++){
            std::cout << "PROCEED" << std::endl;
            if (FD_ISSET(fd, &bufferFDs)){
            
                if (fd == server_socket){
                    // ACCEPT NEW AVAILABLE CONNECTION
                    // Accept but not handle immediately.
                    accept_connection(maxFD);
                    std::cout << "Connection Accepted" << std::endl;
                }
                else{
                    // HANDLE REQUEST
                    // After handling close the client socket
                    
                    // Handle request
                    std::string raw_request = read_socket(fd);
                    //handle_connection(raw_request);
                    std::cout << raw_request << std::endl;
                    // Closing procedure
                    close_connection(maxFD, fd);
                    
                }
            }
        }
    }
}



