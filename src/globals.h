#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <iostream>
#include <string>
#include <vector>
#include <stdarg.h>

#ifndef WINDOWS_CPP
#include <unistd.h>
#else
#include <direct.h>
#endif

using namespace std;

void Output(const string& str)
{
    cout << str << endl;
}

string Input()
{
    string ret;
    cin >> ret;
    return ret;
}

void PrintErr(const string& errmsg)
{
    string str = "[ERROR] ";
    str += errmsg;
    Output(str);
}

void PrintInfo(const string& msg)
{
    string str = "[INFO] ";
    str += msg;
    Output(str);
}

void OutputCmdList(const vector<string>& vec)
{
    if (vec.empty()){
        return;
    }

    Output("Please choose options below:");

    string cmdList;
    int index = 0;
    for (vector<string>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter){
        cmdList += to_string(index);
        cmdList += '.';
        cmdList += *iter;
        cmdList += ' ';
        ++index;
    }

    Output(cmdList);
}

string InputCmdList(const vector<string>& vec)
{
    string input = Input();
    unsigned int index = atoi(input.c_str());
    if (index >= vec.size())
    {
        return "";
    }

    return vec[index];
}

#define MAXPATH 260

string GetAppDir()
{
    char buffer[MAXPATH];
#ifndef WINDOWS_CPP
    getcwd(buffer, MAXPATH);
#else
    _getcwd(buffer, _MAX_PATH);
#endif

    return string(buffer);
}

const unsigned int FORMAT_STRING_BUFFER_SIZE = 16 * 1024;

inline void Format(string& strout, const char* pszOutput, ...)
{
    // code.clean overlength variable(1k) 2017/1/24 l00309883/lishiquan
    char* pBuf = (char*)malloc(FORMAT_STRING_BUFFER_SIZE);
    if (NULL == pBuf)
    {
        strout = "";
        return;
    }
    memset(pBuf, 0, FORMAT_STRING_BUFFER_SIZE);

    va_list vaArgumentList;
    va_start(vaArgumentList, pszOutput);
#ifdef WINDOWS_CPP
    vsprintf_s(pBuf, FORMAT_STRING_BUFFER_SIZE, pszOutput, vaArgumentList);
#else
    vsprintf(pBuf, pszOutput, vaArgumentList);
#endif
    va_end(vaArgumentList);
    strout = pBuf;

    if (NULL != pBuf)
    {
        free(pBuf);
        pBuf = NULL;
    }
}

inline void AppendFormat(string& strout, const char* pszOutput, ...)
{
    // code.clean overlength variable(1k) 2017/1/24 l00309883/lishiquan
    char* pBuf = (char*)malloc(FORMAT_STRING_BUFFER_SIZE);
    if (NULL == pBuf)
    {
        strout = "";
        return;
    }
    memset(pBuf, 0, FORMAT_STRING_BUFFER_SIZE);

    va_list vaArgumentList;
    va_start(vaArgumentList, pszOutput);
#ifdef WINDOWS_CPP
    vsprintf_s(pBuf, FORMAT_STRING_BUFFER_SIZE, pszOutput, vaArgumentList);
#else
    vsprintf(pBuf, pszOutput, vaArgumentList);
#endif
    va_end(vaArgumentList);
    strout += pBuf;

    if (NULL != pBuf)
    {
        free(pBuf);
        pBuf = NULL;
    }
}

#endif
