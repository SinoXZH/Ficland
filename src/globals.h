#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <iostream>
#include <string>
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

#endif
