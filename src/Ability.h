#ifndef __ABILITY_H__
#define __ABILITY_H__

#include "CharaDefine.h"
#include "SocialStatus.h"


class Ability{
public:
    Ability();
    ~Ability();

public:

    void RandomInitAbility(const SocialStatus& sStatus, unsigned int age, GENDER_ENUM gender);

public:
    unsigned int healthPoint;
    unsigned int stamina;
    unsigned int mana;

    unsigned int intelligence;
    unsigned int strength;

    unsigned int fightLevel;
    unsigned int archLevel;
    unsigned int magicLevel;
    unsigned int cureLevel;

    unsigned int secHardness;
    unsigned int secTimelen;
    unsigned int secSkill;
};

#endif
