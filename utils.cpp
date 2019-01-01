#include "util.h"
#include <iostream>
#include <stdarg.h>
#include "GlobalDefine.h"

using namespace std;



std::string Input()
{
    std::string ret;
    std::cin >> ret;

    return ret;
}

void Output(const char* str, ...)
{
    char temp[MAX_STRING_LEN] = {0};
    va_list argList;
    va_start(argList, str);
    vsprintf(temp, str, argList);
    va_end(argList);

    cout << temp << endl;
}

void Output(const string& str)
{
    cout << str << endl;
}

void Format(std::string& srcStr, const char* formatStr, ...)
{
    char temp[MAX_STRING_LEN] = {0};
    va_list argList;
    va_start(argList, formatStr);
    vsprintf(temp, formatStr, argList);
    va_end(argList);

    srcStr = temp;
}
