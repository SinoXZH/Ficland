#ifndef __DOT_MATRIX_H__
#define __DOT_MATRIX_H__

#include "globals.h"
#include "CoDot.h"

const char PLAIN_DOT_CHAR = '+';

class DotMatrix {
public:
    DotMatrix();
    ~DotMatrix();

public:
    bool CreateNewEmptyFile(unsigned int width, unsigned int height);

    bool LoadMatrixFile();

public:
    string filePath;

    unsigned int matrixWidth;
    unsigned int matrixHeight;
    vector<vector<CoDot> > coordinaryMatrix;
};


#endif // __DOT_MATRIX_H__

