#include "Command.hpp"

using namespace std;

const string CommandList::username = "USER";
const string CommandList::account = "ACCT";
const string CommandList::password = "PASS";
const string CommandList::filetype = "TYPE";
const string CommandList::listDirectory = "LIST";
const string CommandList::changeDir = "CDIR";
const string CommandList::deleteFile = "Kill";
const string CommandList::rename = "NAME";
const string CommandList::done = "DONE";
const string CommandList::requestSend = "RETR";
const string CommandList::storeFile = "STOR";

/*-------Helpers---------*/
bool singleArg(string input) {
    if(input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos) {
        return false;
    } else {
        return true;
    }
}

/*-------SeshGremlin---------*/
SeshGremlin::SeshGremlin() {
    hasAccess = false;
    return;
}

// TODO: Implement some different creds
response SeshGremlin::checkCredentials() {
    if(username == "root" || (account == "Blain" && password == "Cribb")) {
        hasAccess = true;
        return loggedIn;
    } else {
        hasAccess = false;
        return success;
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

void UsernameCommand::getResponse(SeshGremlin& session, string& response) {
    session.username = userID;
    if(session.checkCredentials() == loggedIn) {
        response = "!" + userID + " logged in";
    } else if(singleArg(userID)) {
        response = "+User-id valid, send account and password";
    } else {
        response = "-Invalid user-id, try again";
    }
}

/*-------AccountCommand---------*/
AccountCommand::AccountCommand(string command, string account) : Command(command) {
    this->account = account;
}

response AccountCommand::validAccount() {
    if(account == "Blain") {
        return success;
    } else {
        return error;
    }
}

void AccountCommand::getResponse(SeshGremlin& session, string& response) {
    session.account = account;
    if(session.checkCredentials() == loggedIn) {
        response = "!Account valid, logged-in";
    } else if(validAccount()) {
        response = "+User-id valid, send account and password";
    } else {
        response = "-Invalid account, try again";
    }
}

/*-------PasswordCommand---------*/
PasswordCommand::PasswordCommand(string command, string password) : Command(command) {
    this->password = password;
}

void PasswordCommand::getResponse(SeshGremlin& session, string& response) {
    session.password = password;
    if(session.checkCredentials() == loggedIn) {
        response = "!Logged-in";
    } else if(singleArg(password)) {
        response = "+Send account";
    } else {
        response = "-Wrong password, try again";
    }
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


