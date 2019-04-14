#include "Settlement.h"
#include "CoordinaryPoint.h"



Settlement::Settlement(CoordinaryPoint* coPoint, SETTLEMENT_ENUM type)
    : parent(coPoint)
    , settlementType(type)
    , population(0)
    , landLord(NULL)
{
    for (unsigned int i = 0; i < PLACE_ENUM_COUNT; ++i) {
        functionalPlaceList[i] = NULL;
    }
}

Settlement::~Settlement()
{
    for (unsigned int i = 0; i < PLACE_ENUM_COUNT; ++i) {
        if (functionalPlaceList[i] != NULL) {
            delete functionalPlaceList[i];
            functionalPlaceList[i] = NULL;
        }
    }

    for (vector<House*>::iterator iter = residenceList.begin(); iter != residenceList.end(); ++iter) {
        if ((*iter) != NULL) {
            delete (*iter);
            (*iter) = NULL;
        }

        residenceList.clear();
    }
}

bool Settlement::InitSettlement()
{
    return true;
}

void Settlement::InitFuncPlace()
{
    functionalPlaceList[PLACE_LORD_MANSION] = new House();
    functionalPlaceList[PLACE_TAVERN] = new Tavern();
    functionalPlaceList[PLACE_MARKET] = new Market();
    functionalPlaceList[PLACE_MILITARY_CAMP] = new MillitaryCamp();

    if (settlementType >= SETTLEMENT_CITY) {
        functionalPlaceList[PLACE_GOV_OFFICE] = new GovOffice();
        functionalPlaceList[PLACE_POLICE_OFFICE] = new PoliceOffice();
        functionalPlaceList[PLACE_HOSPITAL] = new Hospital();
        
    }

    if (settlementType >= SETTLEMENT_CAPITAL) {
        functionalPlaceList[PLACE_AUCTION_HOUSE] = new AuctionHouse();
        functionalPlaceList[PLACE_ACADEMY] = new Academy();
    }
}

