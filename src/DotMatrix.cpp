#include "DotMatrix.h"
#include <fstream>

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

    ofstream ofs;
    ofs.open(filePath.c_str(), ios_base::out);
    if (!ofs.is_open()) {
        return false;
    }

    string content;

    for (unsigned int h = 0; h < height; ++h) {
        for (unsigned int w = 0; w < width; ++w) {
            content += PLAIN_DOT_CHAR;
            content += ',';
        }
        content += '\n';
    }

    ofs << content;

    ofs.close();

    return true;
}

bool DotMatrix::LoadMatrixFile()
{
    string info;

    ifstream ifs;
    ifs.open(filePath.c_str(), ios_base::in);
    if (!ifs.is_open()) {
        FormatString(info, "Load file failed: %s", filePath.c_str());
        PrintErr(info);
        return false;
    }

    string content;
    string line;
    while (!ifs.eof()) {
        ifs >> line;
        content += line;
        content += '\n';
    }
    ifs.close();

    matrixWidth = 0;
    matrixHeight = 0;
    unsigned int curWidth = 1;

    for (string::iterator iter = content.begin(); iter != content.end(); ++iter) {
        if (*iter == ',') {
            ++curWidth;
            matrixWidth = max(matrixWidth, curWidth);
        }
        else if (*iter == '\n') {
            ++matrixHeight;
            if (curWidth != matrixWidth) {
                FormatString(info, "current width(%d) not equal to matrix width(%d)", 
                curWidth, matrixWidth);
                PrintInfo(info);
                return false;
            }
            
            curWidth = 1;
        }
    }

    if (matrixHeight > 1) {
        --matrixHeight;
    }

    FormatString(info, "Load file: %s, matrix width: %d, matrix height: %d", 
    filePath.c_str(), matrixWidth, matrixHeight);
    PrintInfo(info);

    return true;
}

