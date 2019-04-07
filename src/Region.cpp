#include "Region.h"


unsigned int Region::curRegionId = 0;

Region::Region()
: regionId(0)
, capitalPoint(NULL)
{
    regionId = curRegionId;
    ++curRegionId;
}

Region::~Region()
{
    
}
