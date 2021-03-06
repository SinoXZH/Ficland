#include "WorldMap.h"
#include "CsvParser.h"
#include "XmlManager.h"
#include "TextManager.h"


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

string WorldMap::UniteCharaIdToStringByComma(vector<Character*> charaVector)
{
    string ret;
    for (vector<Character*>::iterator iter = charaVector.begin(); iter != charaVector.end(); ++iter) {
        if (ret.empty()) {
            FormatString(ret, "%d", (*iter)->charaId);
        }
        else {
            FormatString(ret, "%s,%d", ret.c_str(), (*iter)->charaId);
        }
    }

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

                for (unsigned int i = 0; i < PLACE_ENUM_COUNT; ++i) {
                    Place* functionalPlace = settlement->functionalPlaceList[i];
                    if (functionalPlace != NULL) {
                        void* placeNode = xmlMngr.CreateChild(settlementNode, XML_NODE_PLACE);
                        xmlMngr.SetAttribute(placeNode, XML_ATTR_NAME, functionalPlace->placeName);
                        if (functionalPlace->owner != NULL) {
                            xmlMngr.SetAttribute(placeNode, XML_ATTR_OWNER_ID, functionalPlace->owner->charaId);
                        }
                    }
                }

                for (vector<House*>::iterator iter = settlement->residenceList.begin();
                iter != settlement->residenceList.end(); ++iter) {
                    House* residence = *iter;
                    if (residence != NULL) {
                        void* placeNode = xmlMngr.CreateChild(settlementNode, XML_NODE_PLACE);
                        xmlMngr.SetAttribute(placeNode, XML_ATTR_NAME, residence->placeName);
                        if (residence->owner != NULL) {
                            xmlMngr.SetAttribute(placeNode, XML_ATTR_OWNER_ID, residence->owner->charaId);
                        }
                    }
                }
            }   
        }
    }

    void* charasNode = xmlMngr.CreateChild(rootNode, XML_NODE_CHARACTERS);

    for (map<unsigned int, Character*>::iterator iter = characterMap.begin(); iter != characterMap.end(); ++iter) {
        void* charaNode = xmlMngr.CreateChild(charasNode, XML_NODE_CHARACTER);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_ID, iter->first);

        Character* chara = iter->second;
        xmlMngr.SetAttribute(charaNode, XML_ATTR_FAMILY_NAME, chara->familyName);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_NAME, chara->selfName);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_GENDER, chara->charaGender);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_AGE, chara->charaAge);
        xmlMngr.SetAttribute(charaNode, XML_ATTR_RACE, chara->charaRace);

        void* socialstatusNode = xmlMngr.CreateChild(charaNode, XML_NODE_SOCIALSTATUS);
        xmlMngr.SetAttribute(socialstatusNode, XML_ATTR_TITLE, chara->socialStatus.nobleTitle);
        xmlMngr.SetAttribute(socialstatusNode, XML_ATTR_JOB, chara->socialStatus.job);
        xmlMngr.SetAttribute(socialstatusNode, XML_ATTR_STATUS_SCORE, chara->socialStatus.statusScore);

        void* appearanceNode = xmlMngr.CreateChild(charaNode, XML_NODE_APPEARANCE);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_PRETTY_LEVEL, chara->appearance.prettyLevel);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_FITNESS_LEVEL, chara->appearance.fitnessLevel);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_HIGHT, chara->appearance.hight);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_FAT, chara->appearance.fatLevel);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_LEGLENGTH, chara->appearance.legLength);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_SKIN_COLOR, chara->appearance.skinColor);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_HAIR_COLOR, chara->appearance.hairColor);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_HAIR_STYLE, chara->appearance.hairStyle);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_EYE_COLOR, chara->appearance.eyeColor);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_EYE_SIZE, chara->appearance.eyeSize);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_EYE_DEPTH, chara->appearance.eyeDepth);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_EAR_STYLE, chara->appearance.earStyle);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_NOSE_BRIDGE_SIZE, chara->appearance.noseBridgeSize);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_NOSE_WING_SIZE, chara->appearance.noseWingSize);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_MOUTH_WIDTH, chara->appearance.mouthWidth);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_LIPS_THICKNESS, chara->appearance.lipsThickness);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_FACE_LENGTH, chara->appearance.faceLength);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_FACE_WIDTH, chara->appearance.faceWidth);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_EAR_STYLE, chara->appearance.earStyle);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_BEARD, chara->appearance.beard);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_CKSIZE, chara->appearance.ckSize);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_XSIZE, chara->appearance.xSize);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_XRAISE, chara->appearance.xRaise);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_XTSIZE, chara->appearance.xtSize);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_XTDARKNESS, chara->appearance.xtDarkness);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_TSIZE, chara->appearance.tSize);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_TRAISE, chara->appearance.tRaise);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_WAISTSIZE, chara->appearance.waistSize);
        xmlMngr.SetAttribute(appearanceNode, XML_ATTR_SKIN_SMOOTH, chara->appearance.skinSmooth);

        void* personalityNode = xmlMngr.CreateChild(charaNode, XML_NODE_PERSONALITY);
        xmlMngr.SetAttribute(personalityNode, XML_ATTR_OPENNESS, chara->personality.openness);
        xmlMngr.SetAttribute(personalityNode, XML_ATTR_CONSCIENTIOUSNESS, chara->personality.conscientiousness);
        xmlMngr.SetAttribute(personalityNode, XML_ATTR_EXTRAVERSION, chara->personality.extraversion);
        xmlMngr.SetAttribute(personalityNode, XML_ATTR_AGREEABLENESS, chara->personality.agreeableness);
        xmlMngr.SetAttribute(personalityNode, XML_ATTR_NEUROTICISM, chara->personality.neuroticism);
        xmlMngr.SetAttribute(personalityNode, XML_ATTR_SECDESIRE, chara->personality.secDesire);
        xmlMngr.SetAttribute(personalityNode, XML_ATTR_SECDOM, chara->personality.secDomorsub);
        
        void* abilityNode = xmlMngr.CreateChild(charaNode, XML_NODE_ABILITY);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_HEALTHPOINT, chara->ability.healthPoint);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_STAMINA, chara->ability.stamina);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_MANA, chara->ability.mana);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_INTELLIGENCE, chara->ability.intelligence);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_STRENTH, chara->ability.strength);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_FIGHTLEVEL, chara->ability.fightLevel);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_ARCHLEVEL, chara->ability.archLevel);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_MAGICLEVEL, chara->ability.magicLevel);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_CURELEVEL, chara->ability.cureLevel);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_SECSKILL, chara->ability.secSkill);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_SECHARD, chara->ability.secHardness);
        xmlMngr.SetAttribute(abilityNode, XML_ATTR_SECTIME, chara->ability.secTimelen);

        void* relationNode = xmlMngr.CreateChild(charaNode, XML_NODE_RELATIONSHIP);
        if (chara->charaFather != NULL) {
            xmlMngr.SetAttribute(relationNode, XML_ATTR_FATHER, chara->charaFather->charaId);
        }
        if (chara->charaMother != NULL) {
            xmlMngr.SetAttribute(relationNode, XML_ATTR_MOTHER, chara->charaMother->charaId);
        }
        if (chara->charaSpouse != NULL) {
            xmlMngr.SetAttribute(relationNode, XML_ATTR_SPOUSE, chara->charaSpouse->charaId);
        }
        if (!chara->charaConcubines.empty()) {
            xmlMngr.SetAttribute(relationNode, XML_ATTR_CONCUBINES, UniteCharaIdToStringByComma(chara->charaConcubines));
        }
        if (!chara->charaChildren.empty()) {
            xmlMngr.SetAttribute(relationNode, XML_ATTR_CHILDREN, UniteCharaIdToStringByComma(chara->charaChildren));
        }
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

bool WorldMap::GetCharaIntroduction(unsigned int id)
{
    map<unsigned int, Character*>::iterator iter = characterMap.find(id);
    if (iter == characterMap.end()) {
        return false;
    }
    
    Character* chara = iter->second;
    if (chara == NULL) {
        return false;
    }

    return TextManager::GetInstance()->GetCharaIntroduction(chara);
}

