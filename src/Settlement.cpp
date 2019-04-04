#include "Settlement.h"
#include "CoordinaryPoint.h"



Settlement::Settlement(CoordinaryPoint* coPoint, SETTLEMENT_ENUM type)
    : parent(coPoint)
    , settlementType(type)
    , population(0)
    , landLord(NULL)
{

}

Settlement::~Settlement()
{

}

