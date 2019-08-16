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

#define PORT_DEFAULT 8080
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
		cout << "Connection Succeeded\n";
		char buffer[1024] = {0};
		*valread = read(*sock , buffer, 1024); 
		cout << endl << "Response: " << string(buffer) << endl;
	}
}

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	
	// Get user to input ipaddress and port, defaults to localhost:8080
	string ipAddress;
	string sport;
	int port = -1;
	cout << "Please enter IP address of server (default = localhost):\n> ";
	getline(cin, ipAddress);
	if(ipAddress.empty()) {
		ipAddress = "127.0.0.1";
	}
	cout << "\nPlease enter port of server (default = 8080):\n> ";
	getline(cin, sport);
	if(!sport.empty()) {
		stringstream ssport(sport);
		ssport >> port;
	} else {
		port = PORT_DEFAULT;
	}

	// Initialise socket and connect to specified server
	init(&sock, &valread, serv_addr, ipAddress, port);

	string command; 
	char buffer[1024] = {0}; 

	while(1) {
		cout << "\nPlease enter a command:\n> ";
		getline(cin, command);

		if(command.empty()) {
			continue;
		}

		send(sock, command.data(), command.size(), 0); 

		// Receive response
		valread = read(sock, buffer, 1024); 

		cout << string(buffer);
	}
} 
