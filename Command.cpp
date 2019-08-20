#include "Command.hpp"

using namespace std;

/*-------SeshGremlin---------*/
SeshGremlin::SeshGremlin() {
    hasAccess = false;
    directory = "./files";
    return;
}

response SeshGremlin::checkUsername() {
    if(username == "root") {
        hasAccess = true;
        return loggedIn;
    } else if(singleArg(username)) {
        return success;
    } else {
        return error;
    }
}

// TODO: Implement some different creds
response SeshGremlin::checkAccount() {
    if(checkUsername() == loggedIn) {
        hasAccess = true;
        return loggedIn;
    } else if(account == "Blain") {
        if(password == "Cribb") {
            hasAccess = true;
            return loggedIn;
        } else {
            hasAccess = false;
            return success;
        }
    } else {
        hasAccess = false;
        return error;
    }
}

response SeshGremlin::checkPassword() {
    if(checkUsername() == loggedIn) {
        hasAccess = true;
        return loggedIn;
    } else if(account.empty() && singleArg(password)) {
        hasAccess = false;
        return success;
    } else if(account == "Blain" && password == "Cribb") {
        hasAccess = true;
        return loggedIn;
    } else {
        hasAccess = false;
        return error;
    }
}

/*-------Command---------*/
Command::Command(string command) {
    this->command = command;
}

/*-------UsernameCommand---------*/
UsernameCommand::UsernameCommand(string command, string userID) : Command(command) {
    this->userID = userID;
}

void UsernameCommand::getResponse(SeshGremlin& session, string& resp) {
    session.username = userID;
    response respon = session.checkUsername(); 
    if(respon == loggedIn) {
        resp = "!" + userID + " logged in";
    } else if(respon == success) {
        resp = "+User-id valid, send account and password";
    } else {
        resp = "-Invalid user-id, try again";
    }
}

/*-------AccountCommand---------*/
AccountCommand::AccountCommand(string command, string account) : Command(command) {
    this->account = account;
}

void AccountCommand::getResponse(SeshGremlin& session, string& resp) {
    session.account = account;
    response check = session.checkAccount();
    if(check == loggedIn) {
        resp = "!Account valid, logged-in";
    } else if(check == success) {
        resp = "+Account valid, send password";
    } else {
        resp = "-Invalid account, try again";
    }
}

/*-------PasswordCommand---------*/
PasswordCommand::PasswordCommand(string command, string password) : Command(command) {
    this->password = password;
}

void PasswordCommand::getResponse(SeshGremlin& session, string& resp) {
    session.password = password;
    response check = session.checkPassword();
    if(check == loggedIn) {
        resp = "!Logged-in";
    } else if(check == success) {
        resp = "+Send account";
    } else {
        resp = "-Wrong password, try again";
    }
}

/*-------TypeCommand---------*/
TypeCommand::TypeCommand(string command, char type) : Command(command) {
    this->type = type;
}

void TypeCommand::changeType(SeshGremlin& session, string& response) {
    string newType;
    if(type == 'A') {
        newType = "Ascii";
        session.type = ascii;
    } else if(type == 'B') {
        newType = "Binary";
        session.type = bin;
    } else if(type == 'C') {
        newType = "Continuous";
        session.type = con;
    }
    response = "+Using " + newType + " mode";
}

/*-------ListCommand---------*/
// TODO: Add verbosity
ListCommand::ListCommand(string command, bool verbose, string path) : Command(command) {
    this->verbose = verbose;
    this->path = path;
    return;
}

void ListCommand::listDirectory(SeshGremlin& session, string& response) {
    struct dirent *entry;
    string truePath = session.directory + path;
    DIR *directory = opendir(truePath.c_str());

    if(directory == NULL) {
        cout << "Failed to open directory" << endl;
        response = "-Directory doesn't exist";
        return;
    }

    response = "\n+" + session.directory + path + "\n";
    while ((entry = readdir(directory)) != NULL) {
        response = response + entry->d_name + "\n";
    }
    
    closedir(directory);
}

/*-------ChangeCommand---------*/
// TODO: make folder movement less janky
ChangeCommand::ChangeCommand(string command, string path) : Command(command) {
    this->path = path;
    return;
}

void ChangeCommand::changeDir(SeshGremlin& session, string& resp) {
    if(session.directory[session.directory.length() - 1] != '/') {
        session.directory = session.directory + "/";
    }
    DIR *directory = opendir((session.directory + path).c_str());

    if(directory == NULL) {
        cout << "Failed to open directory: " << session.directory + path << endl;
        resp = "-Can't connect to directory because: Doesn't exist";
        closedir(directory);
        return;
    }

    session.directory = session.directory + path;
    resp = "!Changed working dir to " + session.directory;  
}


/*-----------COUT OVERRIDES FOR CLASSES------------*/

//Command
std::ostream& operator<< ( std::ostream& os, const Command& inputCommand) {
   os << string("Command: ") << inputCommand.command << string("\n");

   return os;
}

//UsernameCommand
std::ostream& operator<< ( std::ostream& os, const UsernameCommand& inputCommand) {
   os << string("Command: ") << inputCommand.command << string("\n") << string("UserID: ") << inputCommand.userID << string("\n");

   return os;
}


