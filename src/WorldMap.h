#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__

#include "globals.h"
#include "CoordinaryPoint.h"


class WorldMap {
public:
    WorldMap();
    ~WorldMap();

public:
    bool CreateNewEmptyFile(unsigned int width, unsigned int height);

    bool LoadMatrixFile();

protected:

public:
    string filePath;

    unsigned int matrixWidth;
    unsigned int matrixHeight;
    vector<vector<CoordinaryPoint*> > coordinaryMatrix;
};


#endif // __WORLD_MAP_H__

