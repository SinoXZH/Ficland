#include "DotMatrix.h"
#include "CsvParser.h"


DotMatrix::DotMatrix()
: matrixWidth(0)
, matrixHeight(0)
{

}

DotMatrix::~DotMatrix()
{

}

bool DotMatrix::CreateNewEmptyFile(unsigned int width, unsigned int height)
{
    if (width == 0 || height == 0) {
        return false;
    }

    CsvParser csv;
    return csv.CreateNewCsvFile(filePath, PLAIN_DOT_CHAR, width, height);
}

bool DotMatrix::LoadMatrixFile()
{
    string info;

    CsvParser csv;
    csv.LoadCsvFile(filePath);
    matrixWidth = csv.GetWidth();
    matrixHeight = csv.GetHeight();

    FormatString(info, "Load file: %s, matrix width: %d, matrix height: %d", 
    filePath.c_str(), matrixWidth, matrixHeight);
    PrintInfo(info);

    return true;
}

