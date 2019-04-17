#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__

#include "globals.h"
#include "Region.h"


const string XML_NODE_ROOT = "WORLD_ARCHIVE";
const string XML_NODE_WORLD_MAP = "WORLD_MAP";
const string XML_NODE_REGION = "REGION";
const string XML_NODE_POINT = "POINT";
const string XML_NODE_SETTLEMENT = "SETTLEMENT";
const string XML_NODE_CHARACTERS = "CHARACTERS";
const string XML_NODE_CHARACTER = "CHARA";

const string XML_ATTR_MAP_WIDTH = "MAP_WIDTH";
const string XML_ATTR_MAP_HEIGHT = "MAP_HEIGHT";
const string XML_ATTR_ID = "ID";
const string XML_ATTR_NAME = "NAME";
const string XML_ATTR_FAMILY_NAME = "FAMILY_NAME";
const string XML_ATTR_ISORIENTAL = "ORIENTAL";
const string XML_ATTR_TYPE = "TYPE";
const string XML_ATTR_COORD = "COORD";
const string XML_ATTR_CAPITAL_COORD = "CAPITAL_COORD";
const string XML_ATTR_POINT_COUNT = "POINT_COUNT";
const string XML_ATTR_POPULATION = "POPULATION";
const string XML_ATTR_WEALTH = "WEALTH";
const string XML_ATTR_OWNER_ID = "OWNER_ID";
const string XML_ATTR_MAIN_RACE = "MAIN_RACE";
const string XML_ATTR_RACE = "RACE";
const string XML_ATTR_AGE = "AGE";
const string XML_ATTR_GENDER = "GENDER";
const string XML_ATTR_TITLE = "TITLE";

class WorldMap {

public:
    static WorldMap* GetInstance();
    static void DelInstance();
    
protected:
    WorldMap();
    ~WorldMap();
    

public:
    bool CreateNewEmptyFile(unsigned int width, unsigned int height);

    bool LoadMatrixFile();

    void SetCsvFilePath(const string& filepath) { csvFilePath = filepath; }
    string GetCsvFilePath() { return csvFilePath; }

    void SetXmlFilePath(const string& filepath) { xmlFilePath = filepath; }
    string GetXmlFilePath() { return xmlFilePath; }

    bool SaveWorldToXml();

    bool LoadXmlToWorld();

    bool InitWorldMap();

    CoordinaryPoint* GetPointFromCoord(unsigned int x, unsigned int y);

    Character* NewCharacter();

    static pair<unsigned int, unsigned int> StringCoordToPair(const string& coStr);

    static string NumCoordToString(unsigned int x, unsigned int y);

protected:
    void ClassifyRegion();

    void ClearAllPoints();

    void ClearWorld();

    void ClearAllCharacters();

protected:

    static WorldMap* instance;

    string csvFilePath;
    string xmlFilePath;

    unsigned int matrixWidth;
    unsigned int matrixHeight;
    map<unsigned int, map<unsigned int, CoordinaryPoint*> > coordinaryMatrix;
    vector<Region> regionList;

    map<unsigned int, Character*> characterMap;

public:
    static unsigned int curRegionId;
    static unsigned int curCharaId;
};


#endif // __WORLD_MAP_H__

