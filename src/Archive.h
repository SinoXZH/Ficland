#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include "DotMatrix.h"

#include <string>
using namespace std;

class Archive{
public:
    Archive();
    ~Archive();

public:
    bool CreateNewEmptyMatrixFile(const string& fileName, unsigned int width, unsigned int height);

public:
    static string arcRootDir;
    string arcDir;

    DotMatrix dotMatrix;
};


#endif
