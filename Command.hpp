#include <string>

using namespace std;

// All possible user commands
class CommandList {
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

class Command {
    public:
        string command;
        
        Command(string command);
        
        friend std::ostream& operator << ( std::ostream& os, const Command& inputCommand);
};

class UsernameCommand : public Command {
    public:
        string userID;
        
        UsernameCommand(string command, string userID);
        
        friend std::ostream& operator << ( std::ostream& os, const UsernameCommand& inputCommand);
};

