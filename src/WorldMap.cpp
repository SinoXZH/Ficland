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

    FormatString(info, "Load file: %s, matrix width: %d, matrix height: %d", 
    csvFilePath.c_str(), matrixWidth, matrixHeight);
    PrintInfo(info);

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
        }
    }

    return true;
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
    for (unsigned int h = 0; h < matrixHeight; ++h) {
        for (unsigned int w = 0; w < matrixWidth; ++w) {

            CoordinaryPoint* coPoint = coordinaryMatrix[h][w];
            if (coPoint != NULL) {
                void* pointNode = xmlMngr.CreateChild(coPointsNode, "POINT");
                xmlMngr.SetAttribute(pointNode, "CO_X", coPoint->GetX());
                xmlMngr.SetAttribute(pointNode, "CO_Y", coPoint->GetY());
                xmlMngr.SetAttribute(pointNode, "LANDFORM", (unsigned int)coPoint->GetLandForm());
                Settlement* settlement = coPoint->GetSettlement();
                if (settlement != NULL) {
                    void* settlementNode = xmlMngr.CreateChild(pointNode, "SETTLEMENT");
                    xmlMngr.SetAttribute(settlementNode, "TYPE", settlement->GetSettlmentType());
                }
            }
            
        }
    }

    void* charsNode = xmlMngr.CreateChild(rootNode, "CHARACTERS");

    return xmlMngr.Save();
}

