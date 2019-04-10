#include "WorldMap.h"
#include "CsvParser.h"
#include "XmlManager.h"


WorldMap::WorldMap()
: matrixWidth(0)
, matrixHeight(0)
{

}

WorldMap::~WorldMap()
{
    regionList.clear();

    ClearAllPoints();

    ClearAllCharacters();
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

    Region waterRegion;
    waterRegion.capitalPoint = NULL;
    waterRegion.name = "water";

    Region boundaryRegion;
    boundaryRegion.capitalPoint = NULL;
    boundaryRegion.name = "boundary";

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
                Region region;
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
        xmlMngr.SetAttribute(regionNode, XML_ATTR_ID, regionIter->id);
        xmlMngr.SetAttribute(regionNode, XML_ATTR_NAME, regionIter->name);
        xmlMngr.SetAttribute(regionNode, XML_ATTR_ISORIENTAL, (unsigned int)regionIter->isOriental);
        string capitalCoord;
        if (regionIter->capitalPoint != NULL) {
            FormatString(capitalCoord, "(%d,%d)", regionIter->capitalPoint->GetX(), regionIter->capitalPoint->GetY());
        }
        xmlMngr.SetAttribute(regionNode, XML_ATTR_CAPITAL_COORD, capitalCoord);
        xmlMngr.SetAttribute(regionNode, XML_ATTR_POINT_COUNT, regionIter->regionPoints.size());

        string regionCoords;

        for (vector<CoordinaryPoint*>::iterator pointIter = regionIter->regionPoints.begin();
        pointIter != regionIter->regionPoints.end(); ++pointIter) {

            CoordinaryPoint* coPoint = *pointIter;
            if (coPoint == NULL) {
                PrintErr("NULL coordinary point in region id %d", regionIter->id);
                return false;
            }

            void* pointNode = xmlMngr.CreateChild(regionNode, XML_NODE_POINT);
            xmlMngr.SetAttribute(pointNode, XML_ATTR_CO_X, coPoint->GetX());
            xmlMngr.SetAttribute(pointNode, XML_ATTR_CO_Y, coPoint->GetY());
            xmlMngr.SetAttribute(pointNode, XML_ATTR_TYPE, (unsigned int)coPoint->GetLandForm());
            xmlMngr.SetAttribute(pointNode, XML_ATTR_NAME, coPoint->GetName());
            Settlement* settlement = coPoint->GetSettlement();
            if (settlement != NULL) {
                void* settlementNode = xmlMngr.CreateChild(pointNode, XML_NODE_SETTLEMENT);
                xmlMngr.SetAttribute(settlementNode, XML_ATTR_NAME, settlement->GetName());
                xmlMngr.SetAttribute(settlementNode, XML_ATTR_TYPE, settlement->GetSettlmentType());
            }   
        }
    }

    void* charsNode = xmlMngr.CreateChild(rootNode, XML_NODE_CHARACTERS);

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

    ClearAllPoints();

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

    regionList.clear();

    void* regionNode = xmlMngr.GetFirstChild(coPointsNode);
    while (regionNode != NULL) {
        Region regn;
        regn.id = xmlMngr.GetAttributeNum(regionNode, XML_ATTR_ID);
        regn.name = xmlMngr.GetAttribute(regionNode, XML_ATTR_NAME);
        regn.isOriental = (bool)xmlMngr.GetAttributeNum(regionNode, XML_ATTR_ISORIENTAL);
        string tmp = xmlMngr.GetAttribute(regionNode, XML_ATTR_CAPITAL_COORD);
        if (!tmp.empty()) {
            pair<unsigned int, unsigned int> coPair = StringCoordToPair(tmp);
            regn.capitalPoint = GetPointFromCoord(coPair.first, coPair.second);
        }

        void* pointNode = xmlMngr.GetFirstChild(regionNode);
        while (pointNode != NULL) {
            unsigned int pointX = xmlMngr.GetAttributeNum(pointNode, XML_ATTR_CO_X);
            unsigned int pointY = xmlMngr.GetAttributeNum(pointNode, XML_ATTR_CO_Y);
            CoordinaryPoint* coPoint = GetPointFromCoord(pointX, pointY);
            if (coPoint == NULL) {
                PrintErr("Can not find POINT node(%d,%d) in region point list.", pointX, pointY);
                return false;
            }

            coPoint->SetName(xmlMngr.GetAttribute(pointNode, XML_ATTR_NAME));
            coPoint->SetLandform(xmlMngr.GetAttributeNum(pointNode, XML_ATTR_TYPE));
            coPoint->SetCapitalPoint(regn.capitalPoint);

            void* settlementNode = xmlMngr.GetFirstChild(pointNode);
            if (settlementNode != NULL) {
                unsigned int stType = xmlMngr.GetAttributeNum(settlementNode, XML_ATTR_TYPE);
                Settlement* st = new Settlement(coPoint, (SETTLEMENT_ENUM)stType);
                st->SetName(xmlMngr.GetAttribute(settlementNode, XML_ATTR_NAME));
                coPoint->SetSettlement(st);
            }

            regn.regionPoints.push_back(coPoint);

            pointNode = xmlMngr.GetNextNeighbor(pointNode);
        }

        regionList.push_back(regn);

        regionNode = xmlMngr.GetNextNeighbor(regionNode);
    }

    void* charactersNode = xmlMngr.GetNextNeighbor(coPointsNode);
    
    return true;
}

