#include "globals.h"
#include "Archive.h"
#include "WorldMap.h"
#include "TextManager.h"


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
    WorldMap::GetInstance()->SetCsvFilePath(csvFilePath);

    return WorldMap::GetInstance()->CreateNewEmptyFile(width, height);
}

bool Archive::LoadMatrixFile(const string& fileName)
{
    string csvFilePath = arcDir;
    csvFilePath += PATH_SEPARATOR;
    csvFilePath += fileName;
    WorldMap::GetInstance()->SetCsvFilePath(csvFilePath);

    return WorldMap::GetInstance()->LoadMatrixFile();
}

bool Archive::SaveArchiveToXml()
{
    if (WorldMap::GetInstance()->GetXmlFilePath().empty()) {
        string xmlFilePath = WorldMap::GetInstance()->GetCsvFilePath();
        StringReplace(xmlFilePath, ".csv", ".xml");
        WorldMap::GetInstance()->SetXmlFilePath(xmlFilePath);
    }
    return WorldMap::GetInstance()->SaveWorldToXml();
}

bool Archive::LoadXmlToArchive(const string& fileName)
{
    string xmlFilePath = arcDir;
    xmlFilePath += PATH_SEPARATOR;
    xmlFilePath += fileName;
    WorldMap::GetInstance()->SetXmlFilePath(xmlFilePath);
    return WorldMap::GetInstance()->LoadXmlToWorld();
}

bool Archive::InitWorld()
{
    string textPath = arcDir;
    textPath += PATH_SEPARATOR;
    textPath += "texts";
    TextManager::InitInstance(textPath);
    return WorldMap::GetInstance()->InitWorldMap();
}

bool Archive::GetCharaIntroduction(unsigned int id)
{
    return WorldMap::GetInstance()->GetCharaIntroduction(id);
}
