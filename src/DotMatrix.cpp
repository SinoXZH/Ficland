#include "DotMatrix.h"
#include <fstream>

DotMatrix::DotMatrix()
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
            content += '.';
        }
        content += '\n';
    }

    ofs << content;

    ofs.close();

    return true;
}

