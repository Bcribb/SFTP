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
#include "CommandList.hpp"

#define PORT 8080 
using namespace std;

CommandList cmds = CommandList();
SeshGremlin session = SeshGremlin();

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
    cout << response << endl; 
    send(*new_socket, response.data(), response.size(), 0); 
}

// Directs to operations for different commands
void directory(string inputCommand, string& response) {
    string commandString = inputCommand.substr(0, 4);
    
    response.clear();

    // Username
    if(commandString == cmds.username) {
        if(cmds.checkUsername(inputCommand)) {
            string username = inputCommand.substr(5);
            UsernameCommand command = UsernameCommand(commandString, username); 
            command.getResponse(session, response);
        } else {
            response = "-Invalid user-id, try again";
        }

    // Account
    } else if(commandString == cmds.account) {
        if(cmds.checkAccount(inputCommand)) {
            string account = inputCommand.substr(5);
            AccountCommand command = AccountCommand(commandString, account);
            command.getResponse(session, response);
        } else {
            response = "-Invalid account, try again";
        }

    // Password
    } else if(commandString == cmds.password) {
        if(cmds.checkPassword(inputCommand)) {
            string password = inputCommand.substr(5);
            PasswordCommand command = PasswordCommand(commandString, password);
            command.getResponse(session, response);
        } else {
            response = "-Wrong password, try again";
        }

    // Check at this point whether the user has access
    } else if (!(session.checkPassword() == loggedIn)) {
        response = "-Please log in first";  

    // Type
    } else if(commandString == cmds.filetype) {
        if(cmds.checkFiletype(inputCommand)) {
            char filetype = inputCommand[5];
            TypeCommand command = TypeCommand(commandString, filetype);
            command.changeType(session, response);
        } else {
            response = "-Type not valid";
        }  

    // List
    } else if(commandString == cmds.listDirectory) {
        if(cmds.checkList(inputCommand)) {
            bool verbose = false;
            if(inputCommand.substr(5, 1) == "V") verbose = true;
            string path;
            if(inputCommand.length() > 7) {
                path = inputCommand.substr(7);
            } else {
                path = "";
            }
            ListCommand command = ListCommand(commandString, verbose, path);
            command.listDirectory(session, response);
        } else {
            response = "-Invalid entry";
        }
        

    // Change directory
    } else if(commandString == cmds.changeDir) {
        cout << "CDIR" << endl;
    
    // Delete file
    } else if(commandString == cmds.deleteFile) {
        cout << "Kill" << endl;
    
    // Rename file
    } else if(commandString == cmds.rename) {
        cout << "NAME" << endl;
    
    // Done command
    } else if(commandString == cmds.done) {
        cout << "DONE" << endl;
    
    // Request file
    } else if(commandString == cmds.requestSend) {
        cout << "RETR" << endl;
    
    // Request store
    } else if(commandString == cmds.storeFile) {
        cout << "STOR" << endl;
    
    // They entered something wrong
    } else {
        response = "Invalid command";
        cout << "Invalid command" << endl;
    }
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

        directory(string(buffer), response);
        
        memset(buffer, 0, sizeof(buffer));

        // Send our response to the client
        send(new_socket, response.data(), response.size(), 0); 
    }
} 
