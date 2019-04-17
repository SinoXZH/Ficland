#include "Region.h"


Region::Region(unsigned int id)
: regionId(id)
, capitalPoint(NULL)
, mainRace(RACE_HUMAN_SINIAN)
{
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

    if (coPoint->capitalPoint != NULL) {
        return;
    }

    coPoint->capitalPoint = capitalPoint;
    coPoint->mainRace = mainRace;
    if (coPoint->settlement != NULL) {
        coPoint->settlement->mainRace = mainRace;
    }
    regionPoints.push_back(coPoint);

    SetRegionRecursively(coPoint->GetNorthNeighbor());
    SetRegionRecursively(coPoint->GetSouthNeighbor());
    SetRegionRecursively(coPoint->GetEastNeighbor());
    SetRegionRecursively(coPoint->GetWestNeighbor());
}

CoordinaryPoint* Region::FindPointInRegion(unsigned int x, unsigned int y)
{
    for (vector<CoordinaryPoint*>::iterator iter = regionPoints.begin(); iter != regionPoints.end(); ++iter) {
        if ((*iter)->locationX == x && (*iter)->locationY == y) {
            return *iter;
        }
    }

    return NULL;
}

bool Region::InitRegion()
{
    for (vector<CoordinaryPoint*>::iterator iter = regionPoints.begin(); iter != regionPoints.end(); ++iter) {
        if ((*iter)->InitCoPoint() == false) {
            return false;
        }
    }
    
    return true;
}
