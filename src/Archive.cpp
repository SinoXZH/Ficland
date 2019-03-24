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
    dotMatrix.filePath = arcDir;
    dotMatrix.filePath += PATH_SEPARATOR;
    dotMatrix.filePath += fileName;

    return dotMatrix.CreateNewEmptyFile(width, height);
}

bool Archive::LoadMatrixFile(const string& fileName)
{
    dotMatrix.filePath = arcDir;
    dotMatrix.filePath += PATH_SEPARATOR;
    dotMatrix.filePath += fileName;

    return dotMatrix.LoadMatrixFile();
}
