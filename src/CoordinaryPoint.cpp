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
    , capitalPoint(NULL)
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

list<CoordinaryPoint*> CoordinaryPoint::TravelLandSimple(CoordinaryPoint* start, CoordinaryPoint* destination)
{
    list<CoordinaryPoint*> travelPath;
    list<CoordinaryPoint*> emptyPath;

    if (start == NULL || destination == NULL) {
        return emptyPath;
    }

    travelPath.push_back(start);
    if (start == destination) {
        return travelPath;
    }
    
    CoordinaryPoint* curPoint = start;
    while (curPoint != destination) {
        curPoint = MoveOneStepOnLandSimple(curPoint, destination);
        if (curPoint == NULL) {
            break;
        }

        travelPath.push_back(curPoint);
    }

    if (curPoint == destination) {
        return travelPath;
    }

    return emptyPath;
}

CoordinaryPoint* CoordinaryPoint::MoveOneStepOnLandSimple(CoordinaryPoint* start, CoordinaryPoint* destination)
{
    if (start == NULL || destination == NULL) {
        return NULL;
    }
    if (start == destination) {
        return start;
    }

    vector<CoordinaryPoint*> neighbors;
    if (destination->locationX > start->locationX)

    vector<CoordinaryPoint*> neighbors;
    if (destination->locationX > start->locationX && start->eastNeighbor != NULL && start->eastNeighbor->IsLand()) {
        neighbors.push_back(start->eastNeighbor);
    }
    if (destination->locationX < start->locationX && start->westNeighbor != NULL && start->westNeighbor->IsLand()) {
        neighbors.push_back(start->westNeighbor);
    }
    if (destination->locationY > start->locationY && start->southNeighbor != NULL && start->southNeighbor->IsLand()) {
        neighbors.push_back(start->southNeighbor);
    }
    if (destination->locationY < start->locationY && start->northNeighbor != NULL && start->northNeighbor->IsLand()) {
        neighbors.push_back(start->northNeighbor);
    }

    if (neighbors.size() == 1) {
        return neighbors[0];
    }
    else if (neighbors.size() == 2) {
        unsigned int xDistance = abs((int)(destination->locationX) - (int)(start->locationX));
        unsigned int yDistance = abs((int)(destination->locationY) - (int)(start->locationY));
        return (xDistance >= yDistance) ? neighbors[0] : neighbors[1];
    }
    else if (neighbors.size() == 0) {
        //PrintInfo("Move one step from (%d,%d) to (%d,%d) failed.", start->locationX, start->locationY, destination->locationX, destination->locationY);
        return NULL;
    }

    PrintErr("Valid neighbors size is illegal: %d, while moving one step from (%d,%d) to (%d,%d).", 
        neighbors.size(), start->locationX, start->locationY, destination->locationX, destination->locationY);
    return NULL;
}


