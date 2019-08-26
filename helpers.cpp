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
    FILE *filePointer = fopen((filename).c_str(), "rb");
    int bytesRead;
    char buffer[BUFFER_SIZE];
    while(!feof(filePointer)) {
        if((bytesRead = fread(&buffer, 1, BUFFER_SIZE, filePointer)) > 0) {
            cout << "Sending: " << buffer << endl;
            send(socket, buffer, bytesRead, 0);
        } else {
            break;
        }
    }
    fclose(filePointer);
}

void receiveFile(string filename, int socket, int filesize) {
    size_t datasize;
    char buffer[BUFFER_SIZE];
    int numer = 0;
    ofstream file;
    file.open(filename);
    while(numer < filesize) {
        datasize = recv(socket, buffer, BUFFER_SIZE, 0);
        file << buffer;
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