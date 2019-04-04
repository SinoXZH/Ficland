#ifndef __COORDINARY_POINT_H__
#define __COORDINARY_POINT_H__

#include "globals.h"
#include "Settlement.h"

const string PLAIN_DOT_CHAR = "-";
const string MOUNTIAN_DOT_CHAR = "M";
const string FOREST_DOT_CHAR = "*";
const string DESERT_DOT_CHAR = ".";
const string Boundary_DOT_CHAR = "\\";
const string SUPER_CITY_DOT_CHAR = "S";
const string CITY_DOT_CHAR = "A";
const string TOWN_DOT_CHAR = "B";

typedef enum {
    LANDFORM_WATER = 0,
    LANDFORM_PLAIN,
    LANDFORM_MOUNTAIN,
    LANDFORM_FOREST,
    LANDFORM_DESERT

}LANDFORM_ENUM;

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

    unsigned int GetX() { return locationX; }
    unsigned int GetY() { return locationY; }
    LANDFORM_ENUM GetLandForm() { return landform; }
    Settlement* GetSettlement() { return settlement; }
    string GetName();
    bool IsCapital();
    bool IsBoundary() { return isBoundary; }

    static list<CoordinaryPoint*> TravelBetweenPoint(CoordinaryPoint* start, CoordinaryPoint* destination);

protected:
    unsigned int locationX;
    unsigned int locationY;
    LANDFORM_ENUM landform;
    bool isBoundary;
    string name;

    Settlement* settlement;

    CoordinaryPoint* northNeighbor;
    CoordinaryPoint* southNeighbor;
    CoordinaryPoint* eastNeighbor;
    CoordinaryPoint* westNeighbor;
};

#endif //__COORDINARY_POINT_H__
