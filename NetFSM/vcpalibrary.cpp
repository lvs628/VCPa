#include "vcpalibrary.h"
#include "ctime.h"
//#include "mainwindow.h"

//extern MainWindow *pMainWindow;

//CTime tickT0;

//unsigned long lastUpdateTime;
/*
int64_t  millis()
{
    return pMainWindow->tickT0.elapsed()/1000;
}
*/    
vector<string> splitString(const string& input, char delimiter) {
    vector<std::string> tokens;
    stringstream ss(input);
    string token;

    while (getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

vector<string> splitString(const string& input, const string& delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while (end != string::npos) {
        string token = input.substr(start, end - start);
        if (!token.empty()) {  // Игнорируем пустые подстроки
            result.push_back(token);
        }
        start = end + delimiter.length();
        end = input.find(delimiter, start);
    }
    // Добавляем последний элемент (если не пустой)
    string lastToken = input.substr(start);
    if (!lastToken.empty()) {
        result.push_back(lastToken);
    }
    return result;
}

string itoa(int n) {
    char retbuf[20];
    sprintf(retbuf, "%d", n);
    return string(retbuf);
}
/*
long esp_timer_get_time()
{
    return pMainWindow->tickT0.elapsed()*1000;
}
*/    
