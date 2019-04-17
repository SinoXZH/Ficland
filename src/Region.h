#ifndef __REGION_H__
#define __REGION_H__

#include "globals.h"
#include "CoordinaryPoint.h"

class Region{
public:
    Region(unsigned int id);
    ~Region();

public:
    void SetRegionRecursively(CoordinaryPoint* coPoint);

    bool InitRegion();

    unsigned int GetRegionPointCount() { return regionPoints.size(); }

    CoordinaryPoint* FindPointInRegion(unsigned int x, unsigned int y);

public:
    unsigned int regionId;
    string regionName;
    RACE_ENUM mainRace;
    CoordinaryPoint* capitalPoint;

    vector<CoordinaryPoint*> regionPoints;
};



#endif
