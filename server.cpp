// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <string>
#include <iostream>

#include "Command.hpp"

#define PORT 8080 
using namespace std;

void init(int* server_fd, int* new_socket, int* valread, struct sockaddr_in* address, int* opt, int* addrlen) {
    // Creating socket file descriptor, socket(domain(IPv4 or IPv6), type(TCP or UDP), protocol value)
    if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        cerr << "socket failed"; 
        exit(EXIT_FAILURE); 
    } 

    // Forcefully attaching socket to the port 8080 
    if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, opt, sizeof(*opt))) { 
        cerr << "setsockopt"; 
        exit(EXIT_FAILURE); 
    } 

    // Setting protocol family as IP, listen on all interfaces, and set the port
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080 
    if (bind(*server_fd, (struct sockaddr *)address, sizeof(*address)) < 0) { 
        cerr << "bind failed";
        exit(EXIT_FAILURE); 
    }

    // Open the socket to listen for connections
    if (listen(*server_fd, 3) < 0) 
    { 
        cerr << "listen"; 
        exit(EXIT_FAILURE); 
    } 

    // Block until we can accept a connection to the server
    if ((*new_socket = accept(*server_fd, (struct sockaddr *)address, (socklen_t*)addrlen)) < 0) { 
        cerr << "accept"; 
        exit(EXIT_FAILURE); 
    } 

    string response = "+Blain SFTP Service\0";
    cout << response; 
    send(*new_socket, response.data(), response.size(), 0); 
}

void directory(string inputCommand) {
    
}

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    string response = "\nCommand received\n"; 

    // Initialise the socket and listen for connections
    init(&server_fd, &new_socket, &valread, &address, &opt, &addrlen);

    // Accept connections as they come in
    while (1) {
        // Read in the command, print it
        valread = read(new_socket , buffer, 1024);
        cout << "Command was : " << buffer << endl;
        
        memset(buffer, 0, sizeof(buffer));

        // Send our response to the client
        send(new_socket, response.data(), response.size(), 0); 
    }
} 
