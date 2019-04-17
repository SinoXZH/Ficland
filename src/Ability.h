#ifndef __ABILITY_H__
#define __ABILITY_H__


class Ability{
public:
    Ability();
    ~Ability();

public:
    unsigned int healthPoint;
    unsigned int stamina;
    unsigned int mana;

    unsigned int intelligence;
    unsigned int mentalPower;
    unsigned int strength;
    unsigned int fightLevel;
    unsigned int shootLevel;
    unsigned int magicLevel;

    unsigned int managerLevel;
    unsigned int cookLevel;
};

#endif
