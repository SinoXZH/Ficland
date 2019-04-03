#include "CoordinaryPoint.h"

CoordinaryPoint::CoordinaryPoint(unsigned int x, unsigned int y)
    : locationX(x)
    , locationY(y)
    , landform(LANDFORM_WATER)
    , settlementType(SETTLEMENT_NONE)
    , settlement(NULL)
    , northNeighbor(NULL)
    , southNeighbor(NULL)
    , eastNeighbor(NULL)
    , westNeighbor(NULL)
{

}

CoordinaryPoint::~CoordinaryPoint()
{

}

void CoordinaryPoint::LoadFromSymbol(const string& sym)
{
    if (sym.empty())
    {
        landform = LANDFORM_WATER;
        settlementType = SETTLEMENT_NONE;
    }
    else if (sym == PLAIN_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
        settlementType = SETTLEMENT_NONE;
    }
    else if (sym == MOUNTIAN_DOT_CHAR) {
        landform = LANDFORM_MOUNTAIN;
        settlementType = SETTLEMENT_NONE;
    }
    else if (sym == FOREST_DOT_CHAR) {
        landform = LANDFORM_FOREST;
        settlementType = SETTLEMENT_NONE;
    }
    else if (sym == DESERT_DOT_CHAR) {
        landform = LANDFORM_DESERT;
        settlementType = SETTLEMENT_NONE;
    }
    else if (sym == SUPER_CITY_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
        if (northNeighbor != NULL && northNeighbor->landform != LANDFORM_WATER) {
            landform = northNeighbor->landform;
        }
        settlementType = SETTLEMENT_SUPER_CITY;
    }
    else if (sym == CITY_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
        if (northNeighbor != NULL && northNeighbor->landform != LANDFORM_WATER) {
            landform = northNeighbor->landform;
        }
        settlementType = SETTLEMENT_CITY;
    }
    else if (sym == TOWN_DOT_CHAR) {
        landform = LANDFORM_PLAIN;
        if (northNeighbor != NULL && northNeighbor->landform != LANDFORM_WATER) {
            landform = northNeighbor->landform;
        }
        settlementType = SETTLEMENT_TOWN;
    }
}

