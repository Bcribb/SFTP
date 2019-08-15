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

Command::Command(string command) {
    this->command = command;
}



UsernameCommand::UsernameCommand(string command, string userID) : Command(command) {
    this->userID = userID;
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


