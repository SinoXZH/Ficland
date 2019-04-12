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

}

void Settlement::InitPlaceFromType()
{

}

