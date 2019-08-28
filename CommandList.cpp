#include "CommandList.hpp"

/*-------CommandList---------*/
const string CommandList::username = "USER";
const string CommandList::account = "ACCT";
const string CommandList::password = "PASS";
const string CommandList::filetype = "TYPE";
const string CommandList::listDirectory = "LIST";
const string CommandList::changeDir = "CDIR";
const string CommandList::deleteFile = "KILL";
const string CommandList::rename = "NAME";
const string CommandList::tobe= "TOBE";
const string CommandList::done = "DONE";
const string CommandList::requestSend = "RETR";
const string CommandList::send = "SEND";
const string CommandList::stop = "STOP";
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

bool CommandList::checkList(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    }
    
    char type = input[5];
    if(!((type == 'F') || (type == 'V'))) {
        cout << "INVALID ENTRY: Invalid format" << endl;
        return false;
    }

    if(input.length() > 6 && (input[6] != ' ')) {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    }

    return true;
}

bool CommandList::checkChange(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    } 

    if(!singleArg(input.substr(5))) {
        cout << "INVALID ENTRY: Invalid format" << endl;
        return false;
    }

    return true;
}

bool CommandList::checkDelete(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    } 

    if(!singleArg(input.substr(5))) {
        cout << "INVALID ENTRY: Invalid format" << endl;
        return false;
    }

    return true;
}

bool CommandList::checkRename(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    } 

    if(!singleArg(input.substr(5))) {
        cout << "INVALID ENTRY: Invalid format" << endl;
        return false;
    }

    return true;
}

bool CommandList::checkTobe(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    } 

    if(!singleArg(input.substr(5))) {
        cout << "INVALID ENTRY: Invalid format" << endl;
        return false;
    }

    return true;
}

bool CommandList::checkDone(string input) {
    if(input == "DONE") {
        return true;
    }

    return false;
}

bool CommandList::checkRequest(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    } 

    if(!singleArg(input.substr(5))) {
        cout << "INVALID ENTRY: Invalid format" << endl;
        return false;
    }

    return true;
}

bool CommandList::checkStore(string input) {
    if(input[4] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    } 

    string type = input.substr(5, 3);
    if(type != "NEW" && type != "OLD" && type != "APP") {
        cout << "INVALID ENTRY: Invalid format" << endl;
        return false;
    }

    if(input[8] != ' ') {
        cout << "INVALID ENTRY: Missing space" << endl;
        return false;
    }

    if(!singleArg(input.substr(9))) {
        cout << "INVALID ENTRY: Invalid format" << endl;
        return false;
    }

    return true;
}