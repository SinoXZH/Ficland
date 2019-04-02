#ifndef __DOT_MATRIX_H__
#define __DOT_MATRIX_H__

#include "globals.h"
#include "CoordinaryPoint.h"

const string PLAIN_DOT_CHAR = "+";

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
    vector<vector<CoordinaryPoint> > coordinaryMatrix;
};


#endif // __DOT_MATRIX_H__

