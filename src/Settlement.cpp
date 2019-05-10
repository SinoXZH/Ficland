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
    wealth = GetNormalDistributionUint(50, 10);
    switch (settlementType)
    {
    case SETTLEMENT_TOWN:
        population = GetNormalDistributionUint(10000, 5000);
        break;
    case SETTLEMENT_CITY:
        population = GetNormalDistributionUint(100000, 50000);
        break;
    case SETTLEMENT_CAPITAL:
        population = GetNormalDistributionUint(500000, 100000);
        break;
    default:
        break;
    }

    InitFuncPlace();

    stName = "³¤°²³Ç";

    functionalPlaceList[PLACE_ACADEMY]->functionalGroup = new AcademyGroup();
    AcademyGroup* acdmyGroup = (AcademyGroup*)functionalPlaceList[PLACE_ACADEMY]->functionalGroup;

    //construct landlord character
    landLord = WorldMap::GetInstance()->NewCharacter();
    landLord->InitChara("", GetLordTitleFromPopulation(), JOB_LANDLORD, 0, mainRace);
    landLord->socialStatus.manorName = stName;

    //construct the lord house
    functionalPlaceList[PLACE_LORD_MANSION]->owner = landLord;
    functionalPlaceList[PLACE_LORD_MANSION]->functionalGroup = new Family();
    functionalPlaceList[PLACE_LORD_MANSION]->functionalGroup->SetGroupLeader(landLord);
    functionalPlaceList[PLACE_LORD_MANSION]->functionalGroup->RandomInitGroupMembers();

    Character* acdmyPresident = WorldMap::GetInstance()->NewCharacter();
    acdmyPresident->InitChara("", TITLE_COUNT, JOB_ACADEMY_PRESIDENT, 0, mainRace);
    acdmyGroup->SetGroupLeader(acdmyPresident);
    House* acdmyPresidentHouse = new House();
    acdmyPresidentHouse->owner = acdmyPresident;
    functionalPlaceList[PLACE_ACADEMY]->owner = acdmyPresident;
    acdmyPresidentHouse->functionalGroup = new Family();
    acdmyPresidentHouse->functionalGroup->SetGroupLeader(acdmyPresident);
    acdmyPresidentHouse->functionalGroup->RandomInitGroupMembers();
    residenceList.push_back(acdmyPresidentHouse);

    for (unsigned int i = 0; i < 10; ++i) {
        Character* teacher = WorldMap::GetInstance()->NewCharacter();
        teacher->InitChara("", TITLE_BARON, JOB_ACADEMY_MAGIC_TEACHER, 0, mainRace);
        acdmyGroup->teacherList.push_back(teacher);
        House* teacherHouse = new House();
        teacherHouse->owner = teacher;
        teacherHouse->functionalGroup = new Family();
        teacherHouse->functionalGroup->SetGroupLeader(teacher);
        teacherHouse->functionalGroup->RandomInitGroupMembers();
        residenceList.push_back(teacherHouse);
    }

    for (unsigned int i = 0; i < 10; ++i) {
        Character* teacher = WorldMap::GetInstance()->NewCharacter();
        teacher->InitChara("", TITLE_BARON, JOB_ACADEMY_FIGHTER_TEACHER, 0, mainRace);
        acdmyGroup->teacherList.push_back(teacher);
        House* teacherHouse = new House();
        teacherHouse->owner = teacher;
        teacherHouse->functionalGroup = new Family();
        teacherHouse->functionalGroup->SetGroupLeader(teacher);
        teacherHouse->functionalGroup->RandomInitGroupMembers();
        residenceList.push_back(teacherHouse);
    }

    for (unsigned int i = 0; i < 10; ++i) {
        Character* teacher = WorldMap::GetInstance()->NewCharacter();
        teacher->InitChara("", TITLE_BARON, JOB_ACADEMY_ARCHER_TEACHER, 0, mainRace);
        acdmyGroup->teacherList.push_back(teacher);
        House* teacherHouse = new House();
        teacherHouse->owner = teacher;
        teacherHouse->functionalGroup = new Family();
        teacherHouse->functionalGroup->SetGroupLeader(teacher);
        teacherHouse->functionalGroup->RandomInitGroupMembers();
        residenceList.push_back(teacherHouse);
    }

    functionalPlaceList[PLACE_HOSPITAL]->functionalGroup = new HospitalGroup();
    HospitalGroup* hospitalGroup = (HospitalGroup*)functionalPlaceList[PLACE_HOSPITAL]->functionalGroup;

    Character* hospitalPresident = WorldMap::GetInstance()->NewCharacter();
    hospitalPresident->InitChara("", TITLE_COUNT, JOB_HOSPITAL_PRESIDENT, 0, mainRace);
    hospitalGroup->SetGroupLeader(hospitalPresident);
    House* hospitalPresidentHouse = new House();
    hospitalPresidentHouse->owner = hospitalPresident;
    functionalPlaceList[PLACE_HOSPITAL]->owner = hospitalPresident;
    hospitalPresidentHouse->functionalGroup = new Family();
    hospitalPresidentHouse->functionalGroup->SetGroupLeader(hospitalPresident);
    hospitalPresidentHouse->functionalGroup->RandomInitGroupMembers();
    residenceList.push_back(hospitalPresidentHouse);

    for (unsigned int i = 0; i < 10; ++i) {
        Character* doctor = WorldMap::GetInstance()->NewCharacter();
        doctor->InitChara("", TITLE_BARON, JOB_HOSPITAL_DOCTOR, 0, mainRace);
        hospitalGroup->doctorList.push_back(doctor);
        House* doctorHouse = new House();
        doctorHouse->owner = doctor;
        doctorHouse->functionalGroup = new Family();
        doctorHouse->functionalGroup->SetGroupLeader(doctor);
        doctorHouse->functionalGroup->RandomInitGroupMembers();
        residenceList.push_back(doctorHouse);
    }

    for (unsigned int i = 0; i < 20; ++i) {
        Character* nurse = WorldMap::GetInstance()->NewCharacter();
        nurse->InitChara("", TITLE_NONE, JOB_HOSPITAL_NURSE, 0, mainRace);
        hospitalGroup->doctorList.push_back(nurse);
        House* nurseHouse = new House();
        nurseHouse->owner = nurse;
        nurseHouse->functionalGroup = new Family();
        nurseHouse->functionalGroup->SetGroupLeader(nurse);
        nurseHouse->functionalGroup->RandomInitGroupMembers();
        residenceList.push_back(nurseHouse);
    }

    for (unsigned int i = 0; i < 20; ++i) {
        Character* citizen = WorldMap::GetInstance()->NewCharacter();
        unsigned int citizenAge = GetNormalDistributionUint(38, 3);
        citizen->InitChara("", TITLE_NONE, JOB_CITIZEN, 0, mainRace, citizenAge);
        House* citizenHouse = new House();
        citizenHouse->owner = citizen;
        citizenHouse->functionalGroup = new Family();
        citizenHouse->functionalGroup->SetGroupLeader(citizen);
        citizenHouse->functionalGroup->RandomInitGroupMembers();
        residenceList.push_back(citizenHouse);
    }

    for (vector<Character*>::iterator iter = functionalPlaceList[PLACE_LORD_MANSION]->functionalGroup->memberList.begin(); 
        iter != functionalPlaceList[PLACE_LORD_MANSION]->functionalGroup->memberList.end(); ++iter) {
        if ((*iter)->socialStatus.job == JOB_ACADEMY_STUDENT) {
            acdmyGroup->studentList.push_back(*iter);
        }
    }

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

