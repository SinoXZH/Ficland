#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__

#include "globals.h"
#include "Region.h"


const string XML_NODE_ROOT = "WORLD_ARCHIVE";
const string XML_NODE_WORLD_MAP = "WORLD_MAP";
const string XML_NODE_REGION = "REGION";
const string XML_NODE_POINT = "POINT";
const string XML_NODE_SETTLEMENT = "SETTLEMENT";
const string XML_NODE_PLACE = "PLACE";
const string XML_NODE_CHARACTERS = "CHARACTERS";
const string XML_NODE_CHARACTER = "CHARA";
const string XML_NODE_SOCIALSTATUS = "SOCIALSTATUS";
const string XML_NODE_APPEARANCE = "APPEARANCE";
const string XML_NODE_PERSONALITY = "PERSONALITY";
const string XML_NODE_ABILITY = "ABILITY";

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
const string XML_ATTR_JOB = "JOB";
const string XML_ATTR_PRETTY_LEVEL = "PRETTY";
const string XML_ATTR_FITNESS_LEVEL = "FITNESS";
const string XML_ATTR_SKIN_COLOR = "SKINCOLOR";
const string XML_ATTR_HAIR_COLOR = "HAIRCOLOR";
const string XML_ATTR_HAIR_STYLE = "HAIRSTYLE";
const string XML_ATTR_EYE_COLOR = "EYECOLOR";
const string XML_ATTR_EYE_SIZE = "EYESIZE";
const string XML_ATTR_EYE_DEPTH = "EYEDEPTH";
const string XML_ATTR_EAR_STYLE = "EARSTYLE";
const string XML_ATTR_NOSE_BRIDGE_SIZE = "NOSEBRIDGESIZE";
const string XML_ATTR_NOSE_WING_SIZE = "NOSEWINGSIZE";
const string XML_ATTR_MOUTH_WIDTH = "MOUSEWIDTH";
const string XML_ATTR_LIPS_THICKNESS = "LIPSTHICKNESS";
const string XML_ATTR_FACE_LENGTH = "FACELENGTH";
const string XML_ATTR_FACE_WIDTH = "FACEWIDTH";
const string XML_ATTR_BEARD = "BEARD";
const string XML_ATTR_STRONG_LEVEL = "STRONG";
const string XML_ATTR_XSIZE = "XSIZE";
const string XML_ATTR_XRAISE = "XRAISE";
const string XML_ATTR_XTSIZE = "XTSIZE";
const string XML_ATTR_XTDARKNESS = "XTDARKNESS";
const string XML_ATTR_TSIZE = "TSIZE";
const string XML_ATTR_TRAISE = "TRAISE";
const string XML_ATTR_WAISTSIZE = "WAISTSIZE";
const string XML_ATTR_SKIN_SMOOTH = "SKINSMOOTH";

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

