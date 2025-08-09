#ifndef VCPALIBRARY_H
#define VCPALIBRARY_H
#include <sstream>
#include <vector>
using namespace std;

//int64_t millis();

vector<string> splitString(const string& input, char delimiter);
vector<string> splitString(const string& input, const string& delimiter);

#endif // VCPALIBRARY_H
