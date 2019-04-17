#ifndef __SETTLEMENT_H__
#define __SETTLEMENT_H__

#include "Character.h"
#include "Place.h"

typedef enum {
    SETTLEMENT_NONE = 0,
    SETTLEMENT_TOWN,
    SETTLEMENT_CITY,
    SETTLEMENT_CAPITAL

}SETTLEMENT_ENUM;

class CoordinaryPoint;

class Settlement {
public:
    Settlement(CoordinaryPoint* coPoint, SETTLEMENT_ENUM type);
    ~Settlement();

public:
    SETTLEMENT_ENUM GetSettlmentType() { return settlementType; }

    string GetName() { return name; }

    void SetName(const string& str) { name = str; }

    bool IsCapital() { return settlementType == SETTLEMENT_CAPITAL; }

    bool InitSettlement();

protected:
    void InitFuncPlace();

protected:
    CoordinaryPoint* parent;
    SETTLEMENT_ENUM settlementType;
    string name;
    unsigned int population;
    unsigned int wealth;

    Character* landLord;

    Place* functionalPlaceList[PLACE_ENUM_COUNT];
    vector<House*> residenceList;
};


#endif //__SETTLEMENT_H__
