#include "Settlement.h"
#include "CoordinaryPoint.h"
#include "WorldMap.h"



Settlement::Settlement(CoordinaryPoint* coPoint, SETTLEMENT_ENUM type)
    : parent(coPoint)
    , settlementType(type)
    , population(0)
    , landLord(NULL)
    , mainRace(RACE_UNKNOWN)
{
    for (unsigned int i = 0; i < PLACE_ENUM_COUNT; ++i) {
        functionalPlaceList[i] = NULL;
    }

    if (coPoint != NULL) {
        mainRace = coPoint->mainRace;
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
    wealth = GetNormalDistributionNum(50, 10);
    switch (settlementType)
    {
    case SETTLEMENT_TOWN:
        population = GetNormalDistributionNum(10000, 5000);
        break;
    case SETTLEMENT_CITY:
        population = GetNormalDistributionNum(100000, 50000);
        break;
    case SETTLEMENT_CAPITAL:
        population = GetNormalDistributionNum(500000, 100000);
        break;
    default:
        break;
    }

    InitFuncPlace();

    //construct landlord character
    landLord = WorldMap::GetInstance()->NewCharacter();
    landLord->InitChara(GetLordTitleFromPopulation(), JOB_LANDLORD, mainRace);

    //construct the lord house
    functionalPlaceList[PLACE_LORD_MANSION]->functionalGroup = new Family();
    functionalPlaceList[PLACE_LORD_MANSION]->functionalGroup->SetGroupLeader(landLord);
    functionalPlaceList[PLACE_LORD_MANSION]->functionalGroup->RandomInitGroupMembers();

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

unsigned int Settlement::GetOwnerId()
{
    if (landLord != NULL) {
        return landLord->charaId;
    }

    return 0;
}

TITLE_ENUM Settlement::GetLordTitleFromPopulation()
{
    if (population == 0) {
        return TITLE_NONE;
    }
    else if (0 < population && population <= 1000) {
        return TITLE_BARON;
    }
    else if (1000 < population && population <= 5000) {
        return TITLE_VISCOUNT;
    }
    else if (5000 < population && population <= 20000) {
        return TITLE_COUNT;
    }
    else if (20000 < population && population <= 100000) {
        return TITLE_MARQUIS;
    }
    else if (100000 < population && population <= 500000) {
        return TITLE_DUKE;
    }
    else if (population > 500000) {
        return TITLE_KING;
    }

    return TITLE_NONE;
}

