#include "Region.h"


unsigned int Region::curRegionId = 0;

Region::Region()
: id(0)
, isOriental(false)
, capitalPoint(NULL)
{
    id = curRegionId;
    ++curRegionId;
}

Region::~Region()
{
    
}

void Region::SetRegionRecursively(CoordinaryPoint* coPoint)
{
    if (coPoint == NULL) {
        return;
    }

    if (!coPoint->IsLand()) {
        return;
    }

    if (coPoint->IsBoundary()) {
        return;
    }

    if (coPoint->GetCapitalPoint() != NULL) {
        return;
    }

    coPoint->SetCapitalPoint(capitalPoint);
    regionPoints.push_back(coPoint);

    SetRegionRecursively(coPoint->GetNorthNeighbor());
    SetRegionRecursively(coPoint->GetSouthNeighbor());
    SetRegionRecursively(coPoint->GetEastNeighbor());
    SetRegionRecursively(coPoint->GetWestNeighbor());
}

CoordinaryPoint* Region::FindPointInRegion(unsigned int x, unsigned int y)
{
    for (vector<CoordinaryPoint*>::iterator iter = regionPoints.begin(); iter != regionPoints.end(); ++iter) {
        if ((*iter)->GetX() == x && (*iter)->GetY() == y) {
            return *iter;
        }
    }

    return NULL;
}
