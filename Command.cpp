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
    this.command = command;
}

UsernameCommand::UsernameCommand(string command, string username) : Command(command) {
    id = username;
}