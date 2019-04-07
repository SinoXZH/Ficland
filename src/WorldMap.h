#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__

#include "globals.h"
#include "Region.h"

class WorldMap {
public:
    WorldMap();
    ~WorldMap();

public:
    bool CreateNewEmptyFile(unsigned int width, unsigned int height);

    bool LoadMatrixFile();

    void SetCsvFilePath(const string& filepath) { csvFilePath = filepath; }
    void SetXmlFilePath(const string& filepath) { xmlFilePath = filepath; }

    bool SaveWorldToXml();

protected:
    void ClassifyRegion();

protected:
    string csvFilePath;
    string xmlFilePath;

    unsigned int matrixWidth;
    unsigned int matrixHeight;
    vector<vector<CoordinaryPoint*> > coordinaryMatrix;
    vector<Region> regionList;
};


#endif // __WORLD_MAP_H__

