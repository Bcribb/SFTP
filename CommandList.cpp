#include "CommandList.hpp"

/*-------CommandList---------*/
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

bool CommandList::checkUsername(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    }
    
    string username = input.substr(5);
    if(!singleArg(username)) {
        cout << "INVALID ENTRY: Invalid user-id format" << endl;
        return false;
    }

    return true;
}

bool CommandList::checkAccount(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    }
    
    string account = input.substr(5);
    if(!singleArg(account)) {
        cout << "INVALID ENTRY: Invalid account format" << endl;
        return false;
    }

    return true;
}

bool CommandList::checkPassword(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    }
    
    string password = input.substr(5);
    if(!singleArg(password)) {
        cout << "INVALID ENTRY: Invalid password format" << endl;
        return false;
    }

    return true;
}

bool CommandList::checkFiletype(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    }
    
    char type = input[5];
    if(!((type == 'A') || (type == 'B') || (type == 'C'))) {
        cout << "INVALID ENTRY: Invalid filetype" << endl;
        return false;
    }

    return true;
}