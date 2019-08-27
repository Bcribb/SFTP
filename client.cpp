// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#include "helpers.hpp"

bool connected = false;

#define PORT_DEFAULT 10000
using namespace std;

void init(int* sock, int* valread, struct sockaddr_in &serv_addr, string ipAddress, int port) {
	// Create a socket
	if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		cerr << "Socket creation error \n"; 
		exit(EXIT_FAILURE);
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(port); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	char cstring[ipAddress.size() + 1];
	strcpy(cstring, ipAddress.c_str());
	if(inet_pton(AF_INET, cstring, &serv_addr.sin_addr) <= 0)
	{ 
		cerr << "\nInvalid address\n"; 
		exit(EXIT_FAILURE);
	} 

	cout << endl << "Attempting connection to: " << ipAddress << ":" << port << endl;

	// Attempt to connect to the server
	if (connect(*sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		cerr << "\nConnection Failed\n"; 
		exit(EXIT_FAILURE); 
	} else {
		cout << "Connection Succeeded" << endl;
		connected = true;
		char buffer[1024] = {0};
		*valread = read(*sock , buffer, 1024); 
		cout << endl << "Response: " << string(buffer) << endl;
	}
}

int main(int argc, char const *argv[]) 
{ 
	chdir("client_files");

	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	
	// Get user to input ipaddress and port, defaults to localhost:10000
	string ipAddress;
	string sport;
	int port = -1;
	

	string command; 
	char buffer[1024] = {0}; 

	while(true) {

		// Get input from user to specificy ip and port
		cout << endl << "Please enter IP address of server (default = localhost):" << endl << ">" << flush;
		getline(cin, ipAddress);
		if(ipAddress.empty()) {
			ipAddress = "127.0.0.1";
		}
		cout << endl << "Please enter port of server (default = 10000):" << endl << ">" << flush;
		getline(cin, sport);
		if(!sport.empty()) {
			stringstream ssport(sport);
			ssport >> port;
		} else {
			port = PORT_DEFAULT;
		}

		// Initialise socket and connect to specified server
		init(&sock, &valread, serv_addr, ipAddress, port);

		string filename;
		int filesize;
		string storType;

		while(connected) {
			cout << "\nPlease enter a command:\n> ";
			getline(cin, command);

			if(command.empty()) {
				continue;
			}

			// Pre-checks for specified commands
			if(command == "DONE") {
				connected = false;
			} else if(command.substr(0, 4) == "RETR") {
				filename = command.substr(5);
			} else if(command.substr(0, 4) == "STOR") {
				filename = command.substr(9);
				storType = command.substr(5, 3);
				if(!fileExists(filename)) {
					cout << "-File doesn't exist" << endl;
					continue;
				}
			}

			send(sock, command.data(), command.size(), 0); 

			if(command == "SEND") {
				receiveFile(filename, sock, filesize);

			// Store command follow up
			} else if(command.substr(0, 4) == "STOR") {
				valread = read(sock, buffer, 1024); 
				buffer[valread] = '\0';
				cout << string(buffer) << endl;
				if(buffer[0] == '-') {
					continue;
				}

				string thing = "SIZE " + to_string(getFilesize(filename.c_str()));
				send(sock, thing.data(), thing.size(), 0);

				valread = read(sock, buffer, 1024); 
				buffer[valread] = '\0';
				cout << string(buffer) << endl;

				if(buffer[0] != '+') {
					continue;
				}

				sendFile(filename, sock);

				valread = read(sock, buffer, 1024); 
				buffer[valread] = '\0';
				cout << string(buffer) << endl;

			} else {
				// Receive response
				valread = read(sock, buffer, 1024); 
				buffer[valread] = '\0';
				cout << string(buffer) << endl;
			}

			if((command.substr(0, 4) == "RETR") && (buffer[0] != '-')) {
				filesize = stoi(buffer);
			}
		}
	}
} 
