#include <string>
#include <iostream>
#include "helpers.hpp"

using namespace std;

/*-------CommandList---------*/
/*  Stores definitions of different commands
    and checks validity of inputs */
class CommandList {
    public:
        static const string username;
        static const string account;
        static const string password;
        static const string filetype;
        static const string listDirectory;
        static const string changeDir;
        static const string deleteFile;
        static const string rename;
        static const string done;
        static const string requestSend;
        static const string storeFile;

        bool checkUsername(string input);
        bool checkAccount(string input);
        bool checkPassword(string input);
        bool checkFiletype(string input);
        bool checkList(string input);
};