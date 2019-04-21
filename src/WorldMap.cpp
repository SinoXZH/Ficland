#include "WorldMap.h"
#include "CsvParser.h"
#include "XmlManager.h"

unsigned int WorldMap::curRegionId = 0;
unsigned int WorldMap::curCharaId = 0;

WorldMap* WorldMap::instance = NULL;

WorldMap* WorldMap::GetInstance()
{
    if (instance == NULL) {
        instance = new WorldMap;
    }

    return instance;
}

void WorldMap::DelInstance()
{
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

WorldMap::WorldMap()
: matrixWidth(0)
, matrixHeight(0)
{
    
}

WorldMap::~WorldMap()
{
    ClearWorld();
}

bool WorldMap::CreateNewEmptyFile(unsigned int width, unsigned int height)
{
    if (width == 0 || height == 0) {
        return false;
    }

    CsvParser csv;
    return csv.CreateNewCsvFile(csvFilePath, PLAIN_DOT_CHAR, width, height);
}

bool WorldMap::LoadMatrixFile()
{
    string info;

    CsvParser csv;
    csv.LoadCsvFile(csvFilePath);
    matrixWidth = csv.GetWidth();
    matrixHeight = csv.GetHeight();

    PrintInfo("Load file: %s, matrix width: %d, matrix height: %d", 
    csvFilePath.c_str(), matrixWidth, matrixHeight);

    Region waterRegion(curRegionId++);
    waterRegion.capitalPoint = NULL;
    waterRegion.regionName = "water";

    Region boundaryRegion(curRegionId++);
    boundaryRegion.capitalPoint = NULL;
    boundaryRegion.regionName = "boundary";

    for (unsigned int x = 0; x < matrixWidth; ++x) {
        for (unsigned int y = 0; y < matrixHeight; ++y) {
            CoordinaryPoint* coPoint = new CoordinaryPoint(x, y);

            //set neighbor
            if (x > 0) {
                coordinaryMatrix[x - 1][y]->SetEastNeighbor(coPoint);
                coPoint->SetWestNeighbor(coordinaryMatrix[x - 1][y]);
            }
            if (y > 0) {
                coordinaryMatrix[x][y - 1]->SetSouthNeighbor(coPoint);
                coPoint->SetNorthNeighbor(coordinaryMatrix[x][y - 1]);
            }

            // coordinary is reverse
            coPoint->LoadFromSymbol(csv.csvSymbolMatrix[y][x]);

            coordinaryMatrix[x][y] = coPoint;

            if (coPoint->IsBoundary()) {
                boundaryRegion.regionPoints.push_back(coPoint);
            }
            else if (!coPoint->IsLand()) {
                waterRegion.regionPoints.push_back(coPoint);
            }
            else if (coPoint->IsCapital()) {
                Region region(curRegionId++);
                region.capitalPoint = coPoint;
                regionList.push_back(region);
            }
        }
    }

    regionList.push_back(waterRegion);
    regionList.push_back(boundaryRegion);

    PrintInfo("Initialized region count %d.", regionList.size());

    ClassifyRegion();

    return true;
}

void WorldMap::ClassifyRegion()
{
    for (vector<Region>::iterator iter = regionList.begin(); iter != regionList.end(); ++iter) {
        iter->SetRegionRecursively(iter->capitalPoint);
    }
}

void WorldMap::ClearAllPoints()
{
    for (unsigned int x = 0; x < matrixWidth; ++x) {
        for (unsigned int y = 0; y < matrixHeight; ++y) {
            delete coordinaryMatrix[x][y];
            coordinaryMatrix[x][y] = NULL;
        }
    }
    coordinaryMatrix.clear();
}

void WorldMap::ClearAllCharacters()
{
    for (map<unsigned int, Character*>::iterator iter = characterMap.begin(); iter != characterMap.end(); ++iter) {
        if (iter->second != NULL) {
            delete iter->second;
            iter->second = NULL;
        }
    }
    characterMap.clear();
    curCharaId = 0;
}

void WorldMap::ClearWorld()
{
    regionList.clear();
    curRegionId = 0;
    ClearAllPoints();
    ClearAllCharacters();

}

CoordinaryPoint* WorldMap::GetPointFromCoord(unsigned int x, unsigned int y)
{
    if (x >= matrixWidth || y >= matrixHeight) {
        return NULL;
    }

    return coordinaryMatrix[x][y];
}

pair<unsigned int, unsigned int> WorldMap::StringCoordToPair(const string& coStr)
{
    if (coStr.size() < 5) {
        return make_pair(-1, -1);
    }

    if (coStr[0] != '(' || coStr[coStr.size() - 1] != ')') {
        return make_pair(-1, -1);
    }

    string str = coStr.substr(1, coStr.size() - 2);

    vector<string> splitStrs = StringSplit(str, ",");
    if (splitStrs.size() != 2) {
        return make_pair(-1, -1);
    }

    return make_pair(atoi(splitStrs[0].c_str()), atoi(splitStrs[1].c_str()));
}

string WorldMap::NumCoordToString(unsigned int x, unsigned int y)
{
    string ret;
    FormatString(ret, "(%d,%d)", x, y);
    return ret;
}

bool WorldMap::SaveWorldToXml()
{
    XmlManager xmlMngr;

    if (xmlMngr.CreateNewXml(xmlFilePath) == false) {
        return false;
    }

    if (xmlMngr.LoadXml(xmlFilePath) == false) {
        return false;
    }

    void* rootNode = xmlMngr.CreateRoot(XML_NODE_ROOT);
    void* coPointsNode = xmlMngr.CreateChild(rootNode, XML_NODE_WORLD_MAP);
    xmlMngr.SetAttribute(coPointsNode, XML_ATTR_MAP_WIDTH, matrixWidth);
    xmlMngr.SetAttribute(coPointsNode, XML_ATTR_MAP_HEIGHT, matrixHeight);

    for (vector<Region>::iterator regionIter = regionList.begin(); 
    regionIter != regionList.end(); ++regionIter) {
        void* regionNode = xmlMngr.CreateChild(coPointsNode, XML_NODE_REGION);
        xmlMngr.SetAttribute(regionNode, XML_ATTR_ID, regionIter->regionId);
        xmlMngr.SetAttribute(regionNode, XML_ATTR_NAME, regionIter->regionName);
        xmlMngr.SetAttribute(regionNode, XML_ATTR_MAIN_RACE, regionIter->mainRace);
        string capitalCoord;
        if (regionIter->capitalPoint != NULL) {
            FormatString(capitalCoord, "(%d,%d)", regionIter->capitalPoint->locationX, regionIter->capitalPoint->locationY);
        }
        xmlMngr.SetAttribute(regionNode, XML_ATTR_CAPITAL_COORD, capitalCoord);
        xmlMngr.SetAttribute(regionNode, XML_ATTR_POINT_COUNT, regionIter->regionPoints.size());

        string regionCoords;

        for (vector<CoordinaryPoint*>::iterator pointIter = regionIter->regionPoints.begin();
        pointIter != regionIter->regionPoints.end(); ++pointIter) {

            CoordinaryPoint* coPoint = *pointIter;
            if (coPoint == NULL) {
                PrintErr("NULL coordinary point in region id %d", regionIter->regionId);
                return false;
            }

            void* pointNode = xmlMngr.CreateChild(regionNode, XML_NODE_POINT);
            xmlMngr.SetAttribute(pointNode, XML_ATTR_COORD, NumCoordToString(coPoint->locationX, coPoint->locationY));
            xmlMngr.SetAttribute(pointNode, XML_ATTR_TYPE, (unsigned int)coPoint->landform);
            xmlMngr.SetAttribute(pointNode, XML_ATTR_NAME, coPoint->pointName);
            xmlMngr.SetAttribute(pointNode, XML_ATTR_MAIN_RACE, coPoint->mainRace);
            Settlement* settlement = coPoint->settlement;
            if (settlement != NULL) {
                void* settlementNode = xmlMngr.CreateChild(pointNode, XML_NODE_SETTLEMENT);
                xmlMngr.SetAttribute(settlementNode, XML_ATTR_NAME, settlement->stName);
                xmlMngr.SetAttribute(settlementNode, XML_ATTR_TYPE, settlement->settlementType);
                xmlMngr.SetAttribute(settlementNode, XML_ATTR_POPULATION, settlement->population);
                xmlMngr.SetAttribute(settlementNode, XML_ATTR_WEALTH, settlement->wealth);
                xmlMngr.SetAttribute(settlementNode, XML_ATTR_OWNER_ID, settlement->GetOwnerId());
                xmlMngr.SetAttribute(settlementNode, XML_ATTR_MAIN_RACE, settlement->mainRace);
            }   
        }
    }

    void* charasNode = xmlMngr.CreateChild(rootNode, XML_NODE_CHARACTERS);

    for (map<unsigned int, Character*>::iterator iter = characterMap.begin(); iter != characterMap.end(); ++iter) {
        void* charaNode = xmlMngr.CreateChild(charasNode, XML_NODE_CHARACTER);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_ID, iter->first);

        Character* chara = iter->second;
        xmlMngr.SetAttribute(charaNode, XML_ATTR_GENDER, chara->charaGender);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_TITLE, chara->socialStatus.nobleTitle);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_NAME, chara->selfName);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_FAMILY_NAME, chara->familyName);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_AGE, chara->charaAge);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_RACE, chara->charaRace);
    }

    return xmlMngr.Save();
}

bool WorldMap::LoadXmlToWorld()
{
    XmlManager xmlMngr;

    if (xmlMngr.LoadXml(xmlFilePath) == false) {
        return false;
    }

    void* root = xmlMngr.GetRootNode();
    if (root == NULL) {
        return false;
    }

    if (xmlMngr.GetNodeTag(root) != XML_NODE_ROOT) {
        return false;
    }

    void* coPointsNode = xmlMngr.GetFirstChild(root);
    if (xmlMngr.GetNodeTag(coPointsNode) != XML_NODE_WORLD_MAP) {
        return false;
    }

    unsigned int xmlW = xmlMngr.GetAttributeNum(coPointsNode, XML_ATTR_MAP_WIDTH);
    unsigned int xmlH = xmlMngr.GetAttributeNum(coPointsNode, XML_ATTR_MAP_HEIGHT);

    if (xmlW == 0 || xmlH == 0) {
        return false;
    }

    ClearWorld();

    matrixWidth = xmlW;
    matrixHeight = xmlH;
    for (unsigned int x = 0; x < matrixWidth; ++x) {
        for (unsigned int y = 0; y < matrixHeight; ++y) {
            coordinaryMatrix[x][y] = new CoordinaryPoint(x, y);
            //set neighbor
            if (x > 0) {
                coordinaryMatrix[x - 1][y]->SetEastNeighbor(coordinaryMatrix[x][y]);
                coordinaryMatrix[x][y]->SetWestNeighbor(coordinaryMatrix[x - 1][y]);
            }
            if (y > 0) {
                coordinaryMatrix[x][y - 1]->SetSouthNeighbor(coordinaryMatrix[x][y]);
                coordinaryMatrix[x][y]->SetNorthNeighbor(coordinaryMatrix[x][y - 1]);
            }
        }
    }

    void* regionNode = xmlMngr.GetFirstChild(coPointsNode);
    while (regionNode != NULL) {
        Region regn(curRegionId++);
        regn.regionId = xmlMngr.GetAttributeNum(regionNode, XML_ATTR_ID);
        regn.regionName = xmlMngr.GetAttribute(regionNode, XML_ATTR_NAME);
        regn.mainRace = (RACE_ENUM)xmlMngr.GetAttributeNum(regionNode, XML_ATTR_MAIN_RACE);
        string tmp = xmlMngr.GetAttribute(regionNode, XML_ATTR_CAPITAL_COORD);
        if (!tmp.empty()) {
            pair<unsigned int, unsigned int> coPair = StringCoordToPair(tmp);
            regn.capitalPoint = GetPointFromCoord(coPair.first, coPair.second);
        }

        void* pointNode = xmlMngr.GetFirstChild(regionNode);
        while (pointNode != NULL) {
            pair<unsigned int, unsigned int> coPair = StringCoordToPair(xmlMngr.GetAttribute(pointNode, XML_ATTR_COORD));
            CoordinaryPoint* coPoint = GetPointFromCoord(coPair.first, coPair.second);
            if (coPoint == NULL) {
                PrintErr("Can not find POINT node(%d,%d) in region point list.", coPair.first, coPair.second);
                return false;
            }

            coPoint->pointName = xmlMngr.GetAttribute(pointNode, XML_ATTR_NAME);
            coPoint->SetLandform(xmlMngr.GetAttributeNum(pointNode, XML_ATTR_TYPE));
            coPoint->capitalPoint = regn.capitalPoint;
            coPoint->mainRace = (RACE_ENUM)xmlMngr.GetAttributeNum(pointNode, XML_ATTR_MAIN_RACE);

            void* settlementNode = xmlMngr.GetFirstChild(pointNode);
            if (settlementNode != NULL) {
                unsigned int stType = xmlMngr.GetAttributeNum(settlementNode, XML_ATTR_TYPE);
                Settlement* st = new Settlement(coPoint, (SETTLEMENT_ENUM)stType);
                st->stName = xmlMngr.GetAttribute(settlementNode, XML_ATTR_NAME);
                st->landLord = characterMap[xmlMngr.GetAttributeNum(settlementNode, XML_ATTR_OWNER_ID)];
                st->population = xmlMngr.GetAttributeNum(settlementNode, XML_ATTR_POPULATION);
                st->wealth = xmlMngr.GetAttributeNum(settlementNode, XML_ATTR_WEALTH);
                st->mainRace = (RACE_ENUM)xmlMngr.GetAttributeNum(settlementNode, XML_ATTR_MAIN_RACE);

                coPoint->settlement = st;
            }

            regn.regionPoints.push_back(coPoint);

            pointNode = xmlMngr.GetNextNeighbor(pointNode);
        }

        regionList.push_back(regn);

        regionNode = xmlMngr.GetNextNeighbor(regionNode);
    }

    void* charasNode = xmlMngr.GetNextNeighbor(coPointsNode);
    void* charaNode = xmlMngr.GetFirstChild(charasNode);
    while (charaNode != NULL) {
        Character* chara = NewCharacter();
        chara->selfName = xmlMngr.GetAttribute(charaNode, XML_ATTR_NAME);
        chara->familyName = xmlMngr.GetAttribute(charaNode, XML_ATTR_FAMILY_NAME);
        chara->charaRace = (RACE_ENUM)xmlMngr.GetAttributeNum(charaNode, XML_ATTR_RACE);
        chara->charaAge = xmlMngr.GetAttributeNum(charaNode, XML_ATTR_AGE);
        chara->charaGender = (GENDER_ENUM)xmlMngr.GetAttributeNum(charaNode, XML_ATTR_GENDER);
        chara->socialStatus.nobleTitle = (TITLE_ENUM)xmlMngr.GetAttributeNum(charaNode, XML_ATTR_TITLE);
    }
    
    return true;
}

bool WorldMap::InitWorldMap()
{
    if (regionList.empty()) {
        return false;
    }

    for (vector<Region>::iterator iter = regionList.begin(); iter != regionList.end(); ++iter) {
        if (iter->InitRegion() == false) {
            return false;
        }
    }

    return true;
}

Character* WorldMap::NewCharacter()
{
    Character* chara = new Character(curCharaId);
    characterMap[curCharaId] = chara;
    ++curCharaId;
    return chara;
}

