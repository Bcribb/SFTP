#include "helpers.hpp"

bool singleArg(string input) {
    if(input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_/.") != std::string::npos) {
        return false;
    } else {
        return true;
    }
}
