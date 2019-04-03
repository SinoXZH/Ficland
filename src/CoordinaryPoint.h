#ifndef __COORDINARY_POINT_H__
#define __COORDINARY_POINT_H__

#include "globals.h"
#include "Settlement.h"

const string PLAIN_DOT_CHAR = "-";
const string MOUNTIAN_DOT_CHAR = "M";
const string FOREST_DOT_CHAR = "*";
const string DESERT_DOT_CHAR = ".";
const string SUPER_CITY_DOT_CHAR = "S";
const string CITY_DOT_CHAR = "A";
const string TOWN_DOT_CHAR = "B";

typedef enum {
    LANDFORM_WATER,
    LANDFORM_PLAIN,
    LANDFORM_MOUNTAIN,
    LANDFORM_FOREST,
    LANDFORM_DESERT

}LANDFORM_ENUM;

typedef enum {
    SETTLEMENT_NONE,
    SETTLEMENT_SUPER_CITY,
    SETTLEMENT_CITY,
    SETTLEMENT_TOWN

}SETTLEMENT_ENUM;

class CoordinaryPoint{
public:
    CoordinaryPoint(unsigned int x, unsigned int y);
    ~CoordinaryPoint();

public:
    void LoadFromSymbol(const string& sym);

    void SetNorthNeighbor(CoordinaryPoint* coPoint) { northNeighbor = coPoint; }
    void SetSouthNeighbor(CoordinaryPoint* coPoint) { southNeighbor = coPoint; }
    void SetEastNeighbor(CoordinaryPoint* coPoint) { eastNeighbor = coPoint; }
    void SetWestNeighbor(CoordinaryPoint* coPoint) { westNeighbor = coPoint; }

protected:
    unsigned int locationX;
    unsigned int locationY;
    LANDFORM_ENUM landform;
    SETTLEMENT_ENUM settlementType;

    Settlement* settlement;

    CoordinaryPoint* northNeighbor;
    CoordinaryPoint* southNeighbor;
    CoordinaryPoint* eastNeighbor;
    CoordinaryPoint* westNeighbor;
};

#endif //__COORDINARY_POINT_H__
