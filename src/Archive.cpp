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
    string csvFilePath = arcDir;
    csvFilePath += PATH_SEPARATOR;
    csvFilePath += fileName;
    worldMap.SetCsvFilePath(csvFilePath);

    return worldMap.CreateNewEmptyFile(width, height);
}

bool Archive::LoadMatrixFile(const string& fileName)
{
    string csvFilePath = arcDir;
    csvFilePath += PATH_SEPARATOR;
    csvFilePath += fileName;
    worldMap.SetCsvFilePath(csvFilePath);

    return worldMap.LoadMatrixFile();
}

bool Archive::SaveArchiveToXml()
{
    string xmlFilePath = arcDir;
    xmlFilePath += PATH_SEPARATOR;
    xmlFilePath += ARCHIVE_XML_NAME;
    worldMap.SetXmlFilePath(xmlFilePath);
    return worldMap.SaveWorldToXml();
}

bool Archive::LoadXmlToArchive()
{
    string xmlFilePath = arcDir;
    xmlFilePath += PATH_SEPARATOR;
    xmlFilePath += ARCHIVE_XML_NAME;
    worldMap.SetXmlFilePath(xmlFilePath);
    return worldMap.LoadXmlToWorld();
}
