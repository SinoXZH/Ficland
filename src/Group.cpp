#include "Group.h"

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

    }
    else if (leader == wife) {

    }
}
