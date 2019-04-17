#include "globals.h"
#include <random>


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

void PrintErr(const char* format, ...)
{
    string str;
    char* buffer = (char*)malloc(MAX_STRING_SIZE);
    if (NULL == buffer) {
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

    PrintErr(str);

    if (NULL != buffer) {
        free(buffer);
        buffer = NULL;
    }
}

void PrintInfo(const string& msg)
{
    string str = "[INFO] ";
    str += msg;
    Output(str);
}

void PrintInfo(const char* format, ...)
{
    string str;
    char* buffer = (char*)malloc(MAX_STRING_SIZE);
    if (NULL == buffer) {
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

    PrintInfo(str);

    if (NULL != buffer) {
        free(buffer);
        buffer = NULL;
    }
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

void StringReplace(string &str, const string& src, const string& dst)
{
    if (str.empty() || src.empty()) {
        return;
    }

    string::size_type pos = 0;

    while ((pos = str.find(src, pos)) != string::npos)
    {
        str.replace(pos, src.size(), dst);
        pos += dst.size();
    }
}

vector<string> StringSplit(const string&str, const string& seperator)
{
    vector<string> vec;
    if (str.empty()) {
        return vec;
    }

    string::size_type pos = 0;
    string leftstr = str;
    while (pos != string::npos) {
        string::size_type newPos = str.find_first_of(seperator, pos);
        string sub = str.substr(pos, newPos - pos);
        vec.push_back(sub);
        if (newPos == string::npos) {
            break;
        }
        pos = newPos + 1;
    }

    return vec;
}

bool isFileExists(const string& filepath)
{
    if (filepath.empty()) {
        return false;
    }

#ifdef WINDOWS_CPP
    return (_access(filepath.c_str(), 0) == 0);
#else
    return (access(filepath.c_str(), 0) == 0);
#endif
}

unsigned int GetNormalDistributionNum(unsigned int mean, unsigned int sd)
{
    random_device rd;
    default_random_engine engine(rd());
    normal_distribution<double> dist(mean, sd);
    return lround(dist(engine));
}

unsigned int GetRandomNum(unsigned int min, unsigned int max)
{
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<int> uni(min, max);
    return (unsigned int)uni(engine);
}
