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

const string XML_ATTR_MAP_WIDTH = "MAP_WIDTH";
const string XML_ATTR_MAP_HEIGHT = "MAP_HEIGHT";
const string XML_ATTR_ID = "ID";
const string XML_ATTR_NAME = "NAME";
const string XML_ATTR_ISORIENTAL = "ORIENTAL";
const string XML_ATTR_TYPE = "TYPE";
const string XML_ATTR_CO_X = "CO_X";
const string XML_ATTR_CO_Y = "CO_Y";
const string XML_ATTR_CAPITAL_COORD = "CAPITAL_COORD";
const string XML_ATTR_POINT_COUNT = "POINT_COUNT";

class WorldMap {
public:
    WorldMap();
    ~WorldMap();

public:
    bool CreateNewEmptyFile(unsigned int width, unsigned int height);

    bool LoadMatrixFile();

    void SetCsvFilePath(const string& filepath) { csvFilePath = filepath; }
    void SetXmlFilePath(const string& filepath) { xmlFilePath = filepath; }

    bool SaveWorldToXml();

    bool LoadXmlToWorld();

    CoordinaryPoint* GetPointFromCoord(unsigned int x, unsigned int y);

    static pair<unsigned int, unsigned int> StringCoordToPair(const string& coStr);

protected:
    void ClassifyRegion();

    void ClearAllPoints();

    void ClearAllCharacters();

protected:
    string csvFilePath;
    string xmlFilePath;

    unsigned int matrixWidth;
    unsigned int matrixHeight;
    map<unsigned int, map<unsigned int, CoordinaryPoint*> > coordinaryMatrix;
    vector<Region> regionList;

    map<unsigned int, Character*> characterMap;
};


#endif // __WORLD_MAP_H__

