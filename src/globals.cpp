#include "globals.h"

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

unsigned int InputUint()
{
    unsigned int ret;
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
    if (vec.empty()) {
        return;
    }

    Output("Please choose options below:");

    string cmdList;
    int index = 0;
    for (vector<string>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter) {
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

void FormatString(string& str, const char* format, ...)
{
    char* buffer = (char*)malloc(MAX_STRING_SIZE);
    if (NULL == buffer) {
        str = "";
        return;
    }
    memset(buffer, 0, MAX_STRING_SIZE);

    va_list vaList;
    va_start(vaList, format);
#ifdef WINDOWS_CPP
    vsprintf_s(buffer, MAX_STRING_SIZE, format, vaList);
#else
    vsprintf(buffer, format, vaList);
#endif
    va_end(vaList);
    str = buffer;

    if (NULL != buffer) {
        free(buffer);
        buffer = NULL;
    }
}

void AppendFormatString(string& str, const char* format, ...)
{
    char* buffer = (char*)malloc(MAX_STRING_SIZE);
    if (NULL == buffer) {
        str = "";
        return;
    }
    memset(buffer, 0, MAX_STRING_SIZE);

    va_list varList;
    va_start(varList, format);
#ifdef WINDOWS_CPP
    vsprintf_s(buffer, MAX_STRING_SIZE, format, varList);
#else
    vsprintf(buffer, format, varList);
#endif
    va_end(varList);
    str += buffer;

    if (NULL != buffer) {
        free(buffer);
        buffer = NULL;
    }
}
