#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
using namespace std;

typedef enum{
    LOG_INFO,
    LOG_ERROR
}ENUM_LOG_LEVEL;

string Input();

void Output(const char* str, ...);

void Output(const string& str);

void Format(string& srcStr, const char* formatStr, ...);

void PrintLog(ENUM_LOG_LEVEL level, const char* formatStr, ...);



#endif //__UTILS_H__