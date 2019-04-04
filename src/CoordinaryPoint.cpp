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
    else if (sym == SUPER_CITY_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
        if (northNeighbor != NULL && northNeighbor->landform != LANDFORM_WATER) {
            landform = northNeighbor->landform;
        }
        settlement = new Settlement(this, SETTLEMENT_SUPER_CITY);
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

