#ifndef HELPERS

#include <string>
#include <sys/stat.h>

using namespace std;

bool singleArg(string input);
bool fileExists(const string& name);
int getFilesize(const char* filename);

#endif