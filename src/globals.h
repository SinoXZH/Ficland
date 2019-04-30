#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <stdarg.h>
#include <fstream>


#ifndef WINDOWS_CPP
#include <unistd.h>
#else
#include <direct.h>
#include <corecrt_io.h>
#endif

using namespace std;

//global variables
#ifndef WINDOWS_CPP
const char PATH_SEPARATOR = '/';
#else
const char PATH_SEPARATOR = '\\';
#endif

#define MAXPATH 260

const unsigned int MAX_STRING_SIZE = 16 * 1024;


//global functions
void Output(const string& str);

string Input();

unsigned int InputUint();

void PrintErr(const string& errmsg);

void PrintErr(const char* format, ...);

void PrintInfo(const string& msg);

void PrintInfo(const char* format, ...);

void OutputCmdList(const vector<string>& vec);

string InputCmdList(const vector<string>& vec);

string GetAppDir();

void FormatString(string& str, const char* format, ...);

void AppendFormatString(string& str, const char* format, ...);

void StringReplace(string &str, const string& src, const string& dst);

vector<string> StringSplit(const string&str, const string& seperator);

bool isFileExists(const string& filepath);

unsigned int GetNormalDistributionUnsignedNum(unsigned int mean, unsigned int sd);

unsigned int GetRandomNum(unsigned int min, unsigned int max);

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

#endif

