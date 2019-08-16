#include <string>
#include <stdlib.h>

enum response {loggedIn, success, error};

using namespace std;

/*-------CommandList---------*/
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
};

/*-------SeshGremlin---------*/
class SeshGremlin {
    public:
        string username;
        string account;
        string password;
        bool hasAccess;

        SeshGremlin();
        response checkCredentials();
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

        AccountCommand(string Command, string account);

        response validAccount();
        void getResponse(SeshGremlin& session, string& reponse);
};

/*-------PasswordCommand---------*/
class PasswordCommand : public Command {
    public:
        string password;

        PasswordCommand(string Command, string password);

        void getResponse(SeshGremlin& session, string& response);
};
