#ifndef __WORLD_MAP_H__
#define __WORLD_MAP_H__

#include "globals.h"
#include "CoordinaryPoint.h"


typedef struct _REGION_STRU{
    _REGION_STRU()
    : regionId(0)
    , capitalPoint(NULL)
    {
        regionId = curRegionId;
        ++curRegionId;
    }

    unsigned int regionId;
    string regionName;
    CoordinaryPoint* capitalPoint;

    vector<CoordinaryPoint*> regionPoints;

    static unsigned int curRegionId;
}REGION_STRU;

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
    vector<REGION_STRU> regionList;
};


#endif // __WORLD_MAP_H__

