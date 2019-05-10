#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__



#include <string>
using namespace std;

const string ARCHIVE_XML_NAME = "archive.xml";

class Archive{
public:
    Archive();
    ~Archive();

public:
    bool CreateNewEmptyMatrixFile(const string& fileName, unsigned int width, unsigned int height);
    bool LoadMatrixFile(const string& fileName);
    bool SaveArchiveToXml();
    bool LoadXmlToArchive(const string& fileName);
    bool InitWorld();
    bool GetCharaIntroduction(unsigned int id);

public:
    static string arcRootDir;
    string arcDir;
};


#endif
