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
    if (leader->charaAge < 18) {
        return;
    }

    if (leader == husband) {
        wife = WorldMap::GetInstance()->NewCharacter();
        unsigned int wifeAge = GetNormalDistributionUint(husband->charaAge - 2, 3);
        unsigned int wifeStatusScore = (unsigned int)((double)husband->socialStatus.statusScore * 0.8);
        wife->InitChara("", TITLE_NONE, JOB_NONE, wifeStatusScore, husband->charaRace, wifeAge, GENDER_FEMALE);
        memberList.push_back(wife);
        RandomInitConcubines();
    }
    else if (leader == wife) {
        husband = WorldMap::GetInstance()->NewCharacter();
        unsigned int husbandAge = GetNormalDistributionUint(wife->charaAge + 2, 3);
        unsigned int husbandStatusScore = (unsigned int)((double)wife->socialStatus.statusScore * 0.8);
        husband->InitChara("", TITLE_NONE, JOB_NONE, husbandStatusScore, wife->charaRace, husbandAge, GENDER_MALE);
        memberList.push_back(husband);
    }

    RandomInitChildren(husband, wife);
    for (vector<Character*>::iterator iter = concubines.begin(); iter != concubines.end(); ++iter) {
        RandomInitChildren(husband, *iter);
    }

    husband->charaSpouse = wife;
    wife->charaSpouse = husband;
}

void Family::RandomInitConcubines()
{
    if (leader == wife) {
        return;
    }

    unsigned int ccbnCount = husband->socialStatus.statusScore / 10;
    for (unsigned int i = 0; i < ccbnCount; ++i) {
        Character* ccbn = WorldMap::GetInstance()->NewCharacter();
        ccbn->charaSpouse = husband;
        husband->charaConcubines.push_back(ccbn);
        unsigned int ccbnAge = GetNormalDistributionUint(CONCUBINE_EVERAGE_AGE, 3);
        unsigned int ccbnStatusScore = (unsigned int)((double)husband->socialStatus.statusScore * 0.3);
        ccbn->InitChara("", TITLE_NONE, JOB_CONCUBINE, ccbnStatusScore, husband->charaRace, ccbnAge, GENDER_FEMALE);
        concubines.push_back(ccbn);
        memberList.push_back(ccbn);
    }
}

void Family::RandomInitChildren(Character* father, Character* mother)
{
    unsigned int childrenCount = GetNormalDistributionUint(3, 2);
    for (unsigned int i = 0; i < childrenCount; ++i) {
        unsigned int childAge = GetNormalDistributionUint(min(father->charaAge, mother->charaAge) - 18, 2);
        if (childAge == 0 || childAge < 13 || childAge > min(father->charaAge, mother->charaAge) - 15) {
            continue;
        }

        Character* child = WorldMap::GetInstance()->NewCharacter();
        child->charaFather = father;
        child->charaMother = mother;
        father->charaChildren.push_back(child);
        mother->charaChildren.push_back(child);
        JOB_ENUM childJob = JOB_NONE;
        if (12 < childAge && childAge < 25) {
            childJob = JOB_ACADEMY_STUDENT;
        }

        unsigned int childStatusScore = (unsigned int)((double)max(father->socialStatus.statusScore, mother->socialStatus.statusScore) * 0.6);

        child->InitChara(familyName, TITLE_NONE, childJob, childStatusScore, husband->charaRace, childAge, Character::RandomInitGender());
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

void HospitalGroup::SetGroupLeader(Character* chara)
{
    if (chara == NULL) {
        return;
    }

    president = chara;
    leader = chara;
}
