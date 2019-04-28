#ifndef __ABILITY_H__
#define __ABILITY_H__

#include "SocialStatus.h"


class Ability{
public:
    Ability();
    ~Ability();

public:
    void RandomInitAbility(unsigned int score);

    void RandomInitAbility(JOB_ENUM job);

public:
    unsigned int healthPoint;
    unsigned int stamina;
    unsigned int mana;

    unsigned int intelligence;
    unsigned int strength;
    unsigned int fightLevel;
    unsigned int shootLevel;
    unsigned int magicLevel;

    unsigned int managerLevel;
    unsigned int cookLevel;
};

#endif
