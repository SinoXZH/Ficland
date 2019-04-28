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

    memberList.push_back(chara);
}

void Family::RandomInitGroupMembers()
{
    if (leader == husband) {
        wife = WorldMap::GetInstance()->NewCharacter();
        unsigned int wifeAge = GetNormalDistributionNum(husband->charaAge - 2, 5);
        wife->InitChara(husband->socialStatus.nobleTitle, JOB_NONE, husband->charaRace, wifeAge, GENDER_FEMALE);
        memberList.push_back(wife);
        RandomInitConcubines();
    }
    else if (leader == wife) {
        husband = WorldMap::GetInstance()->NewCharacter();
        unsigned int husbandAge = GetNormalDistributionNum(husband->charaAge + 2, 5);
        husband->InitChara(wife->socialStatus.nobleTitle, JOB_NONE, wife->charaRace, husbandAge, GENDER_MALE);
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

    unsigned int ccbnCount = (unsigned int)husband->socialStatus.nobleTitle * 2;
    for (unsigned int i = 0; i < ccbnCount; ++i) {
        Character* ccbn = WorldMap::GetInstance()->NewCharacter();
        unsigned int ccbnAge = GetNormalDistributionNum(CONCUBINE_EVERAGE_AGE, 10);
        ccbn->InitChara(TITLE_NONE, JOB_CONCUBINE, husband->charaRace, ccbnAge, GENDER_FEMALE);
        concubines.push_back(ccbn);
        memberList.push_back(ccbn);
    }
}

void Family::RandomInitChildren(Character* father, Character* mother)
{
    unsigned int childrenCount = GetNormalDistributionNum(3, 2);
    for (unsigned int i = 0; i < childrenCount; ++i) {
        Character* child = WorldMap::GetInstance()->NewCharacter();
        unsigned int childAge = GetNormalDistributionNum(min(father->charaAge, mother->charaAge) - 18, 3);
        child->InitChara(TITLE_NONE, JOB_ACADEMY_STUDENT, husband->charaRace, childAge, Character::RandomInitGender());
        children.push_back(child);
        memberList.push_back(child);
    }
}
