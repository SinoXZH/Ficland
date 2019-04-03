#include "WorldMap.h"
#include "CsvParser.h"


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
    return csv.CreateNewCsvFile(filePath, PLAIN_DOT_CHAR, width, height);
}

bool WorldMap::LoadMatrixFile()
{
    string info;

    CsvParser csv;
    csv.LoadCsvFile(filePath);
    matrixWidth = csv.GetWidth();
    matrixHeight = csv.GetHeight();

    FormatString(info, "Load file: %s, matrix width: %d, matrix height: %d", 
    filePath.c_str(), matrixWidth, matrixHeight);
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

