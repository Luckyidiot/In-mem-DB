#include <iostream>
#include <cstring>      // For memset
#include <sys/socket.h> // For socket functions
#include <arpa/inet.h>  // For sockaddr_in and inet_addr
#include <unistd.h>     // For close()

int main() {
    // 1. Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    // 2. Define server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(6309);                 // Server port
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP

    // 3. Connect to the server
    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection to server failed!" << std::endl;
        close(clientSocket);
        return -1;
    }
    std::cout << "Connected to server!" << std::endl;

    // 4. Send data
    const char* message = "Hello, Server!";
    ssize_t bytesSent = send(clientSocket, message, strlen(message), 0);
    if (bytesSent < 0) {
        std::cerr << "Failed to send data!" << std::endl;
    } else {
        std::cout << "Data sent: " << message << std::endl;
    }

    // 5. Close the socket
    close(clientSocket);
    return 0;
}
