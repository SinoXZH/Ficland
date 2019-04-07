#ifndef __REGION_H__
#define __REGION_H__

#include "globals.h"
#include "CoordinaryPoint.h"

class Region{
public:
    Region();
    ~Region();

protected:
    static unsigned int curRegionId;

public:
    unsigned int regionId;
    string regionName;
    CoordinaryPoint* capitalPoint;

    vector<CoordinaryPoint*> regionPoints;
};



#endif
