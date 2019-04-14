#ifndef __REGION_H__
#define __REGION_H__

#include "globals.h"
#include "CoordinaryPoint.h"

class Region{
public:
    Region();
    ~Region();

public:
    void SetRegionRecursively(CoordinaryPoint* coPoint);

    bool InitRegion();

    unsigned int GetRegionPointCount() { return regionPoints.size(); }

    CoordinaryPoint* FindPointInRegion(unsigned int x, unsigned int y);

protected:
    static unsigned int curRegionId;

public:
    unsigned int id;
    string name;
    CoordinaryPoint* capitalPoint;

    vector<CoordinaryPoint*> regionPoints;
};



#endif
