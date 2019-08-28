// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <string>
#include <iostream>

#include "CommandList.hpp"

#define PORT 10000 
using namespace std;

CommandList cmds = CommandList();
SeshGremlin session;
int new_socket;

void init(int* server_fd, int* new_socket, int* valread, struct sockaddr_in* address, int* opt, int* addrlen) {
    // Creating socket file descriptor, socket(domain(IPv4 or IPv6), type(TCP or UDP), protocol value)
    if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        cerr << "socket failed"; 
        exit(EXIT_FAILURE); 
    } 

    // Forcefully attaching socket to the port 
    if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, opt, sizeof(*opt))) { 
        cerr << "setsockopt"; 
        exit(EXIT_FAILURE); 
    } 

    // Setting protocol family as IP, listen on all interfaces, and set the port
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(PORT);

    // Forcefully attaching socket to the port 
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

    // Done command
    } else if(commandString == cmds.done) {
        if(cmds.checkDone(inputCommand)) {
            response = "+Connection closed";
            send(new_socket, response.data(), response.size(), 0); 
            close(session.newSocket);
            session.open = false;
        } else {
            response = "-Invalid entry";
        }

    // Check at this point whether the user has access
    } else if (session.checkPassword() == error) {
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
        if(cmds.checkChange(inputCommand)) {
            string path = inputCommand.substr(5);
            ChangeCommand command = ChangeCommand(commandString, path);
            command.changeDir(session, response);
        } else {
            response = "-Can't connect to directory because: Invalid entry";
        }
    
    // Delete file
    } else if(commandString == cmds.deleteFile) {
        if(cmds.checkDelete(inputCommand)) {
            string filename = inputCommand.substr(5);
            DeleteCommand command = DeleteCommand(commandString, filename);
            command.deleteFile(session, response);
        } else {
            response = "-Not deleted because: Invalid entry";
        }
    
    // Rename file
    } else if(commandString == cmds.rename) {
        string filename = inputCommand.substr(5);
        if(cmds.checkRename(inputCommand)) {
            RenameCommand command = RenameCommand(commandString, filename);
            command.setTarget(session, response);
        } else {
            session.renamingFile.clear();
            if(session.directory[session.directory.length() - 1] != '/') {
                session.directory = session.directory + "/";
            }
            response = "-Can't find " + session.directory + filename;
        }

    // Renames sub call, TOBE
    } else if(commandString == cmds.tobe) {
        if(cmds.checkTobe(inputCommand)) {
            if(session.renamingFile.empty()) {
                response = "-File wasn't renamed because: No file specified";
            } else {
                string filename = inputCommand.substr(5);
                TobeCommand command = TobeCommand(commandString, filename);
                command.changeName(session, response);
                session.renamingFile.clear();
            }
        }
    
    // Request file
    } else if(commandString == cmds.requestSend) {
        if(cmds.checkRequest(inputCommand)) {
            string filename = inputCommand.substr(5);
            RequestCommand command = RequestCommand(commandString, filename);
            command.request(session, response);
            cout << response << endl;
            if(response[0] == '-') return;
            send(new_socket, response.data(), response.size(), 0); 
            char buffer[1024];
            session.transferDone = false;
            while(!session.transferDone) {
                read(new_socket, buffer, 1024);
                commandString = string(buffer).substr(0, 4);
                cout << "Command was : " << command << endl;
                if(commandString == cmds.stop) {
                    response = "+ok, RETR aborted";
                    session.transferDone = true;
                } else if(commandString == cmds.send) {
                    command.send(session, new_socket);
                    session.transferDone = true;
                } else {
                    response = "-Please reply with either SEND or STOP";
                    send(new_socket, response.data(), response.size(), 0); 
                }
            }            
        } else {
            response = "-Invalid entry";
        }
    
    // Request store
    } else if(commandString == cmds.storeFile) {
        if(cmds.checkStore(inputCommand)) {
            string type = inputCommand.substr(5, 3);
            string filename = inputCommand.substr(9);

            // Find whether we need to create new file or hwat
            StoreCommand command = StoreCommand(commandString, type, filename);
            command.store(session, response);

            // Tell them the answer
            send(new_socket, response.data(), response.size(), 0); 

            // Read the filesize
            char buffer[1024];
            read(new_socket, buffer, 1024);
            int filesize = stoi(string(buffer).substr(5));

            // Check we have space
            if(enoughSpace(filesize)) {
                response = "+ok, waiting for file";
                send(new_socket, response.data(), response.size(), 0); 
            } else {
                response = "-Not enough room, don't send it oh god please";
                send(new_socket, response.data(), response.size(), 0); 
                return;
            }

            // Receive the file
            command.doTheThing(session, filesize, new_socket);

            response = "+Saved " + filename;

        } else {
            response = "-Invalid entry";
        }
    
    // They entered something wrong
    } else {
        response = "Invalid command";
        cout << "Invalid command" << endl;
    }

    // Clear renaming file if user is aborting that command
    if((commandString != cmds.tobe) && (commandString != cmds.rename)) {
        session.renamingFile.clear();
    }
}

int main(int argc, char const *argv[]) 
{ 
    int server_fd, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    string response = "\nCommand received\n"; 

    // Initialise the socket and listen for connections
    init(&server_fd, &new_socket, &valread, &address, &opt, &addrlen);

    // Accept connections as they come in
    while (true) {
        cout << "Waiting for a connection..." << endl;

        // Block until we can accept a connection to the server
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) { 
            cerr << "accept failed\n"; 
            exit(EXIT_FAILURE); 
        } 

        string response = "+Blain SFTP Service\0";
        cout << response << endl; 

        send(new_socket, response.data(), response.size(), 0); 

        session = SeshGremlin();
        readUsers(session.userList);

        while(session.open) {
            // Read in the command, print it
            valread = read(new_socket, buffer, 1024);
            cout << "Command was : " << buffer << endl;

            directory(string(buffer), response);
            
            // Send our response to the client
            if((string(buffer).substr(0, 4) != cmds.requestSend) || (response[0] = '-')) {
                send(new_socket, response.data(), response.size(), 0);
            }

            memset(buffer, 0, sizeof(buffer));
        }
    }
} 
