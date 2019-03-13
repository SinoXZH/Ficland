#ifndef __DOT_MATRIX_H__
#define __DOT_MATRIX_H__

#include <string>
using namespace std;

const char PLAIN_DOT_CHAR = '+';

class DotMatrix {
public:
    DotMatrix();
    ~DotMatrix();

public:
    bool CreateNewEmptyFile(unsigned int width, unsigned int height);

public:
    string filePath;

};


#endif // __DOT_MATRIX_H__

