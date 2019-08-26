#ifndef HELPERS

#include <string>
#include <sys/stat.h>
#include <sys/socket.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define BUFFER_SIZE 1024

using namespace std;

bool singleArg(string input);
bool fileExists(const string& name);
int getFilesize(const char* filename);
void sendFile(string filename, int socket);
void receiveFile(string filename, int socket, int filesize);
int stringToInt(string input);
string intToString(int input);

#endif