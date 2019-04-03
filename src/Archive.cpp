#include "globals.h"
#include "Archive.h"


string Archive::arcRootDir;

Archive::Archive()
{

}

Archive::~Archive()
{

}

bool Archive::CreateNewEmptyMatrixFile(const string& fileName, unsigned int width, unsigned int height)
{
    worldMap.filePath = arcDir;
    worldMap.filePath += PATH_SEPARATOR;
    worldMap.filePath += fileName;

    return worldMap.CreateNewEmptyFile(width, height);
}

bool Archive::LoadMatrixFile(const string& fileName)
{
    worldMap.filePath = arcDir;
    worldMap.filePath += PATH_SEPARATOR;
    worldMap.filePath += fileName;

    return worldMap.LoadMatrixFile();
}
