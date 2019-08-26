#include "helpers.hpp"
#include <unistd.h>

bool singleArg(string input) {
    if(input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_/.") != std::string::npos) {
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
        char buffer[BUFFER_SIZE + 1];
        int sent = 0;

        file.seekg(0, file.end);
        int length = file.tellg();
        file.seekg(0, file.beg);

        while(length > 0) {
            file.read(buffer, BUFFER_SIZE - 1);
            buffer[file.gcount()] = '\0';
            cout << "SENDING:" << endl << string(buffer) << endl;
            send(socket, buffer, file.gcount(), 0);
            length -= file.gcount();
        }
    }
    file.close();
}

void receiveFile(string filename, int socket, int filesize) {
    size_t datasize;
    char buffer[BUFFER_SIZE];
    int numer = 0;
    ofstream file;
    file.open(filename);
    while(numer < filesize) {
        datasize = recv(socket, buffer, BUFFER_SIZE, 0);
        cout << "RECEIVED: " << endl << buffer << endl;
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