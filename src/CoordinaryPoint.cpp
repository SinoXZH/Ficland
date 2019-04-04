#include "CoordinaryPoint.h"

CoordinaryPoint::CoordinaryPoint(unsigned int x, unsigned int y)
    : locationX(x)
    , locationY(y)
    , landform(LANDFORM_WATER)
    , settlement(NULL)
    , northNeighbor(NULL)
    , southNeighbor(NULL)
    , eastNeighbor(NULL)
    , westNeighbor(NULL)
    , isBoundary(false)
{

}

CoordinaryPoint::~CoordinaryPoint()
{
    if (settlement != NULL) {
        delete settlement;
        settlement = NULL;
    }
}

void CoordinaryPoint::LoadFromSymbol(const string& sym)
{
    if (sym.empty())
    {
        landform = LANDFORM_WATER;
    }
    else if (sym == PLAIN_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
    }
    else if (sym == MOUNTIAN_DOT_CHAR) {
        landform = LANDFORM_MOUNTAIN;
    }
    else if (sym == FOREST_DOT_CHAR) {
        landform = LANDFORM_FOREST;
    }
    else if (sym == DESERT_DOT_CHAR) {
        landform = LANDFORM_DESERT;
    }
    else if (sym == Boundary_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
        isBoundary = true;
        if (northNeighbor != NULL && northNeighbor->landform != LANDFORM_WATER) {
            landform = northNeighbor->landform;
        }
    }
    else if (sym == SUPER_CITY_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
        if (northNeighbor != NULL && northNeighbor->landform != LANDFORM_WATER) {
            landform = northNeighbor->landform;
        }
        settlement = new Settlement(this, SETTLEMENT_CAPITAL);
    }
    else if (sym == CITY_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
        if (northNeighbor != NULL && northNeighbor->landform != LANDFORM_WATER) {
            landform = northNeighbor->landform;
        }
        settlement = new Settlement(this, SETTLEMENT_CITY);
    }
    else if (sym == TOWN_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
        if (northNeighbor != NULL && northNeighbor->landform != LANDFORM_WATER) {
            landform = northNeighbor->landform;
        }
        settlement = new Settlement(this, SETTLEMENT_TOWN);
    }
}

string CoordinaryPoint::GetName()
{
    if (settlement != NULL) {
        return settlement->GetName();
    }

    return name;
}

bool CoordinaryPoint::IsCapital()
{
    if (settlement == NULL) {
        return false;
    }

    return settlement->IsCapital();
}

list<CoordinaryPoint*> CoordinaryPoint::TravelBetweenPoint(CoordinaryPoint* start, CoordinaryPoint* destination)
{
    list<CoordinaryPoint*> travelPath;
    if (start == NULL || destination == NULL) {
        return travelPath;
    }

    travelPath.push_back(start);
    if (start == destination) {
        return travelPath;
    }

    while (start->locationX != destination->locationX) {
        if (start->locationX < destination->locationX) {
            start = start->eastNeighbor;
        }
        else{
            start = start->westNeighbor;
        }
        travelPath.push_back(start);
    }
    
    while (start->locationY != destination->locationY) {
        if (start->locationY < destination->locationY) {
            start = start->southNeighbor;
        }
        else{
            start = start->northNeighbor;
        }
        travelPath.push_back(start);
    }

    return travelPath;
}

