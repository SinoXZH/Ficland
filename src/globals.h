#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
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
    int index = atoi(input.c_str());
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
    getcwd(buffer, MAXPATH);

    return string(buffer);
}

#endif
