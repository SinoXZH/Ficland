#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include <string>
using namespace std;

class Archive{
public:
    Archive();
    ~Archive();

public:
    bool CreateNewEmptyMatrixFile(const string& fileName);

public:
    static string arcRootDir;
    string arcDir;

};


#endif
