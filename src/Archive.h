#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include "WorldMap.h"

#include <string>
using namespace std;

class Archive{
public:
    Archive();
    ~Archive();

public:
    bool CreateNewEmptyMatrixFile(const string& fileName, unsigned int width, unsigned int height);
    bool LoadMatrixFile(const string& fileName);

public:
    static string arcRootDir;
    string arcDir;

    WorldMap worldMap;
};


#endif
