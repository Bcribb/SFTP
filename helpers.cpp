#include "helpers.hpp"
#include <unistd.h>

bool singleArg(string input) {
    if(input.empty()) {
        return false;
    }
    if(input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_/.()") != std::string::npos) {
        return false;
    } else {
        return true;
    }
}

bool fileExists(const string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

int getFilesize(const char* filename) {
    struct stat fileStats;
    if(stat(filename, &fileStats)) {
        return 0;
    }
    return fileStats.st_size;
}

void sendFile(string filename, int socket) {
    ifstream file(filename, ifstream::binary);
    if(file) {
        char buffer[BUFFER_SIZE];
        int sent = 0;

        file.seekg(0, file.end);
        int length = file.tellg();
        file.seekg(0, file.beg);

        while(length > 0) {
            // memset(buffer, 0, sizeof(buffer));
            file.read(buffer, BUFFER_SIZE);
            send(socket, buffer, file.gcount(), 0);
            length -= file.gcount();
        }
    }
    file.close();
}

void receiveFile(string filename, int socket, int filesize, bool append) {
    size_t datasize;
    char buffer[BUFFER_SIZE];
    int numer = 0;
    ofstream file;
    if(append) {
        file.open(filename, fstream::app);
    } else {
        file.open(filename);
    } 
    while(numer < filesize) {
        // memset(buffer, 0, sizeof(buffer));
        datasize = read(socket, buffer, BUFFER_SIZE);
        buffer[datasize] = '\0';
        file.write(buffer, datasize);
        numer += datasize;
    }
    file.close();
}

int stringToInt(string input) {
    stringstream ss(input);
    int out = 0;
    ss >> out;
    return out;
}

string intToString(int input) {
    ostringstream ss;
    ss << input;
    string out = ss.str();
    return out;
}

bool enoughSpace(int input) {
    return true;
}

string newFilename(string directory, string filename) {
    int count = 1;
    string newFilename = filename + "(" + to_string(count) + ")";
    while(fileExists(directory + newFilename)) {
        count++;
        newFilename = filename + "(" + to_string(count) + ")";
    }
    return newFilename;
}

void readUsers(userDef userList[10]) {
    ifstream file;
    file.open("users.txt");
    string line;
    int count = 0;

    while(getline(file, line) && count < 10) {
        userList[count].username = line.substr(0, line.find(" "));
        userList[count].account = line.substr(userList[count].username.length() + 1, line.find(" ", userList[count].username.length() + 1) - (userList[count].username.length() + 1));
        userList[count].password = line.substr(userList[count].username.length() + userList[count].account.length() +  2);
        count++;
    }
}

bool checkLoggedIn(userDef userList[10], string username, string account, string password) {
    for(int i = 0; i < 10; i++) {
        if(userList[i].username == username && userList[i].account == account && userList[i].password == password) {
            return true;
        }
    }
    return false;
}

bool checkUser(userDef userList[10], string username) {
    for(int i = 0; i < 10; i++) {
        if(userList[i].username == username) {
            return true;
        }
    }
    return false;
}

bool checkAcc(userDef userList[10], string username, string account) {
    for(int i = 0; i < 10; i++) {
        if(userList[i].username == username && userList[i].account == account) {
            return true;
        }
    }
    return false;
}