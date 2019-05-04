#include "Group.h"
#include "WorldMap.h"

Group::Group()
    : leader(NULL)
{

}

Group::~Group()
{

}

void Family::SetGroupLeader(Character* chara)
{
    if (chara->charaGender == GENDER_UNKNOWN) {
        return;
    }

    leader = chara;
    if (chara->charaGender == GENDER_MALE) {
        husband = chara;
    }
    else {
        wife = chara;
    }

    familyName = chara->familyName;

    memberList.push_back(chara);
}

void Family::RandomInitGroupMembers()
{
    if (leader == husband) {
        wife = WorldMap::GetInstance()->NewCharacter();
        unsigned int wifeAge = GetNormalDistributionUnsignedNum(husband->charaAge - 2, 3);
        wife->InitChara("", husband->socialStatus.nobleTitle, JOB_NONE, husband->charaRace, wifeAge, GENDER_FEMALE);
        memberList.push_back(wife);
        RandomInitConcubines();
    }
    else if (leader == wife) {
        husband = WorldMap::GetInstance()->NewCharacter();
        unsigned int husbandAge = GetNormalDistributionUnsignedNum(wife->charaAge + 2, 3);
        husband->InitChara("", wife->socialStatus.nobleTitle, JOB_NONE, wife->charaRace, husbandAge, GENDER_MALE);
        memberList.push_back(husband);
    }

    RandomInitChildren(husband, wife);
    for (vector<Character*>::iterator iter = concubines.begin(); iter != concubines.end(); ++iter) {
        RandomInitChildren(husband, *iter);
    }
}

void Family::RandomInitConcubines()
{
    if (leader == wife) {
        return;
    }

    unsigned int ccbnCount = (unsigned int)husband->socialStatus.nobleTitle + 1;
    for (unsigned int i = 0; i < ccbnCount; ++i) {
        Character* ccbn = WorldMap::GetInstance()->NewCharacter();
        unsigned int ccbnAge = GetNormalDistributionUnsignedNum(CONCUBINE_EVERAGE_AGE, 3);
        ccbn->InitChara("", TITLE_NONE, JOB_CONCUBINE, husband->charaRace, ccbnAge, GENDER_FEMALE);
        concubines.push_back(ccbn);
        memberList.push_back(ccbn);
    }
}

void Family::RandomInitChildren(Character* father, Character* mother)
{
    unsigned int childrenCount = GetNormalDistributionUnsignedNum(3, 2);
    for (unsigned int i = 0; i < childrenCount; ++i) {
        unsigned int childAge = GetNormalDistributionUnsignedNum(min(father->charaAge, mother->charaAge) - 20, 3);
        if (childAge == 0) {
            continue;
        }

        Character* child = WorldMap::GetInstance()->NewCharacter();
        JOB_ENUM childJob = JOB_NONE;
        if (12 < childAge && childAge < 25) {
            childJob = JOB_ACADEMY_STUDENT;
        }
        child->InitChara(familyName, TITLE_NONE, childJob, husband->charaRace, childAge, Character::RandomInitGender());
        children.push_back(child);
        memberList.push_back(child);
    }
}

void AcademyGroup::SetGroupLeader(Character* chara)
{
    if (chara == NULL) {
        return;
    }

    president = chara;
    leader = chara;
}
