#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <iostream>

#include "helpers.hpp"

enum response {loggedIn, success, error};
enum filetype {ascii, bin, con};

using namespace std;

/*-------SeshGremlin---------*/
class SeshGremlin {
    public:
        string username;
        string account;
        string password;

        filetype type;
        string directory;
        string currentFile;

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
        char type;

        TypeCommand(string command, char type);

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

/*-------ChangeCommand---------*/
class ChangeCommand : public Command {
    public:
        string path;

        ChangeCommand(string command, string path);

        void changeDir(SeshGremlin& session, string& response);
};

/*-------DeleteCommand---------*/
class DeleteCommand : public Command {
    public:
        string filename;

        DeleteCommand(string command, string filename);

        void deleteFile(SeshGremlin& session, string& response);
};

/*-------RenameCommand---------*/
class RenameCommand : public Command {
    public:
        string filename;

        RenameCommand(string command, string filename);

        void setTarget(SeshGremlin& session, string& response);
};

/*-------TobeCommand---------*/
class TobeCommand : public Command {
    public:
        string filename;

        TobeCommand(string command, string filename);

        void changeName(SeshGremlin& session, string& response);
};
