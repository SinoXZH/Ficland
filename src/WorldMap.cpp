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
    for (unsigned int h = 0; h < matrixHeight; ++h) {
        for (unsigned int w = 0; w < matrixWidth; ++w) {
            delete coordinaryMatrix[h][w];
            coordinaryMatrix[h][w] = NULL;
        }
    }
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

    Region boundaryRegion;
    boundaryRegion.capitalPoint = NULL;
    boundaryRegion.regionName = "boundary";

    for (unsigned int h = 0; h < matrixHeight; ++h) {
        for (unsigned int w = 0; w < matrixWidth; ++w) {

            if (h >= coordinaryMatrix.size()) {
                vector<CoordinaryPoint*> vec;
                coordinaryMatrix.push_back(vec);
            }

            CoordinaryPoint* coPoint = new CoordinaryPoint(w, h);

            //set neighbor
            if (h > 0) {
                coordinaryMatrix[h - 1][w]->SetSouthNeighbor(coPoint);
                coPoint->SetNorthNeighbor(coordinaryMatrix[h - 1][w]);
            }
            if (w > 0) {
                coordinaryMatrix[h][w - 1]->SetEastNeighbor(coPoint);
                coPoint->SetWestNeighbor(coordinaryMatrix[h][w - 1]);
            }

            coPoint->LoadFromSymbol(csv.csvSymbolMatrix[h][w]);

            coordinaryMatrix[h].push_back(coPoint);

            if (coPoint->IsBoundary()) {
                boundaryRegion.regionPoints.push_back(coPoint);
            } else if (coPoint->IsCapital()) {
                Region region;
                region.capitalPoint = coPoint;
                regionList.push_back(region);
            }
        }
    }

    regionList.push_back(boundaryRegion);

    PrintInfo("Initialized region count %d.", regionList.size());

    ClassifyRegion();

    return true;
}

void WorldMap::ClassifyRegion()
{
    for (unsigned int h = 0; h < matrixHeight; ++h) {
        for (unsigned int w = 0; w < matrixWidth; ++w) {
            
            CoordinaryPoint* coPoint = coordinaryMatrix[h][w];
            if (coPoint->IsBoundary()) {
                continue;
            }

            for (vector<Region>::iterator iter = regionList.begin(); 
            iter != regionList.end(); ++iter) {

                bool inCurRegion = true;

                CoordinaryPoint* capital = iter->capitalPoint;
                list<CoordinaryPoint*> travelList = CoordinaryPoint::TravelBetweenPoint(coPoint, capital);
                for (list<CoordinaryPoint*>::iterator travelIter = travelList.begin(); 
                travelIter != travelList.end(); ++travelIter) {
                    if ((*travelIter)->IsBoundary()) {
                        inCurRegion = false;
                        break;
                    }
                }

                if (inCurRegion)
                {
                    iter->regionPoints.push_back(coPoint);
                }
            }
        }
    }
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

    void* rootNode = xmlMngr.CreateRoot("WORLD_ARCHIVE");
    void* coPointsNode = xmlMngr.CreateChild(rootNode, "COORDINARY_POINTS");

    for (vector<Region>::iterator regionIter = regionList.begin(); 
    regionIter != regionList.end(); ++regionIter) {
        void* regionNode = xmlMngr.CreateChild(coPointsNode, "REGION");
        xmlMngr.SetAttribute(regionNode, "ID", regionIter->regionId);
        xmlMngr.SetAttribute(regionNode, "NAME", regionIter->regionName);

        for (vector<CoordinaryPoint*>::iterator pointIter = regionIter->regionPoints.begin();
        pointIter != regionIter->regionPoints.end(); ++pointIter) {

            CoordinaryPoint* coPoint = *pointIter;
            if (coPoint == NULL) {
                PrintErr("NULL coordinary point in region id %d", regionIter->regionId);
                return false;
            }

            void* pointNode = xmlMngr.CreateChild(regionNode, "POINT");
            xmlMngr.SetAttribute(pointNode, "CO_X", coPoint->GetX());
            xmlMngr.SetAttribute(pointNode, "CO_Y", coPoint->GetY());
            xmlMngr.SetAttribute(pointNode, "LANDFORM", (unsigned int)coPoint->GetLandForm());
            xmlMngr.SetAttribute(pointNode, "NAME", coPoint->GetName());
            Settlement* settlement = coPoint->GetSettlement();
            if (settlement != NULL) {
                void* settlementNode = xmlMngr.CreateChild(pointNode, "SETTLEMENT");
                xmlMngr.SetAttribute(settlementNode, "NAME", settlement->GetName());
                xmlMngr.SetAttribute(settlementNode, "TYPE", settlement->GetSettlmentType());
            }   
        }
    }

    void* charsNode = xmlMngr.CreateChild(rootNode, "CHARACTERS");

    return xmlMngr.Save();
}

