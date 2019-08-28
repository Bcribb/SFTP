#ifndef HELPERS

#include <string>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define BUFFER_SIZE 1024

using namespace std;

struct userDef {
    string username;
    string account;
    string password;
};

bool singleArg(string input);
bool fileExists(const string& name);
int getFilesize(const char* filename);
void sendFile(string filename, int socket);
void receiveFile(string filename, int socket, int filesize, bool append);
int stringToInt(string input);
string intToString(int input);
bool enoughSpace(int input);
string newFilename(string directory, string filename);
void readUsers(userDef userList[10]);
bool checkLoggedIn(userDef userList[10], string username, string acount, string password);
bool checkUser(userDef userList[10], string username);
bool checkAcc(userDef userList[10], string username, string account);

#endif