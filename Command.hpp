#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>

enum response {loggedIn, success, error};
enum filetype {ascii, bin, con};

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
};

/*-------SeshGremlin---------*/
class SeshGremlin {
    public:
        string username;
        string account;
        string password;

        filetype type;
        string directory;

        bool hasAccess;

        SeshGremlin();
        response checkUsername();
        response checkAccount();
        response checkPassword();
};

/*-------Command---------*/
class Command {
    public:
        string command;
        
        Command(string command);
        
        friend std::ostream& operator << ( std::ostream& os, const Command& inputCommand);
};

/*-------UsernameCommand---------*/
class UsernameCommand : public Command {
    public:
        string userID;
        
        UsernameCommand(string command, string userID);
        void getResponse(SeshGremlin& session, string& reponse);
        
        friend std::ostream& operator << ( std::ostream& os, const UsernameCommand& inputCommand);
};

/*-------AccountCommand---------*/
class AccountCommand : public Command {
    public:
        string account;

        AccountCommand(string command, string account);

        response validAccount();
        void getResponse(SeshGremlin& session, string& reponse);
};

/*-------PasswordCommand---------*/
class PasswordCommand : public Command {
    public:
        string password;

        PasswordCommand(string command, string password);

        void getResponse(SeshGremlin& session, string& response);
};

/*-------TypeCommand---------*/
class TypeCommand : public Command {
    public:
        string type;

        TypeCommand(string command, string type);

        void changeType(SeshGremlin& session, string& response);
};

/*-------TypeCommand---------*/
class ListCommand : public Command {
    public:
        bool verbose;
        string path;

        ListCommand(string command, bool verbose, string path);

        void listDirectory(SeshGremlin& session, string& response);
};
