#ifndef __SETTLEMENT_H__
#define __SETTLEMENT_H__

#include "Character.h"
#include "Place.h"

typedef enum {
    SETTLEMENT_NONE = 0,
    SETTLEMENT_SUPER_CITY,
    SETTLEMENT_CITY,
    SETTLEMENT_TOWN

}SETTLEMENT_ENUM;

class CoordinaryPoint;

class Settlement {
public:
    Settlement(CoordinaryPoint* coPoint, SETTLEMENT_ENUM type);
    ~Settlement();

public:
    SETTLEMENT_ENUM GetSettlmentType() { return settlementType; }

protected:
    CoordinaryPoint* parent;
    SETTLEMENT_ENUM settlementType;
    unsigned int population;
    Character* landLord;

    vector<Place*> placeList;
};


#endif //__SETTLEMENT_H__

