#include "Ability.h"
#include "globals.h"


Ability::Ability()
    : healthPoint(0)
    , stamina(0)
    , mana(0)
    , intelligence(0)
    , strength(0)
    , fightLevel(0)
    , archLevel(0)
    , magicLevel(0)
    , cureLevel(0)
    , secHardness(0)
    , secTimelen(0)
    , secSkill(0)
{

}

Ability::~Ability()
{

}

void Ability::RandomInitAbility(const SocialStatus& sStatus, unsigned int age, GENDER_ENUM gender)
{
    unsigned int mean = 0;
    unsigned int sd = 10;

    //intelligence
    mean += sStatus.statusScore;
    if (sStatus.job == JOB_ACADEMY_MAGIC_TEACHER
        || sStatus.job == JOB_HOSPITAL_DOCTOR
        || sStatus.job == JOB_ACADEMY_PRESIDENT
        || sStatus.job == JOB_HOSPITAL_PRESIDENT) {
        mean += 30;
    }
    else if (sStatus.job == JOB_ACADEMY_ARCHER_TEACHER) {
        mean += 10;
    }
    mean += age;
    intelligence = GetNormalDistributionUint(mean, sd);

    //strength
    mean = 0;
    mean += sStatus.statusScore;
    if (sStatus.job == JOB_ACADEMY_FIGHTER_TEACHER) { 
        mean += 30;
    }
    else if (sStatus.job == JOB_ACADEMY_ARCHER_TEACHER) {
        mean += 10;
    }
    mean += age;
    if (gender == GENDER_FEMALE) {
        mean = (unsigned int)((double)mean * 0.8);
    }
    strength = GetNormalDistributionUint(mean, sd);

    healthPoint = GetNormalDistributionUint(strength * 10, sd * 10);

    stamina = GetNormalDistributionUint(strength, sd);

    mean = intelligence;
    if (sStatus.job == JOB_ACADEMY_MAGIC_TEACHER) {
        mean += 10;
    }
    magicLevel = GetNormalDistributionUint(mean, sd);
    mana = GetNormalDistributionUint(magicLevel * 5, sd * 5);

    mean = strength;
    if (sStatus.job == JOB_ACADEMY_FIGHTER_TEACHER) {
        mean += 30;
    }
    fightLevel = GetNormalDistributionUint(mean, sd);

    mean = (strength + intelligence) / 2;
    if (sStatus.job == JOB_ACADEMY_ARCHER_TEACHER) {
        mean += 30;
    }
    archLevel = GetNormalDistributionUint(mean, sd);

    if (sStatus.job == JOB_HOSPITAL_DOCTOR) {
        cureLevel = GetNormalDistributionUint(intelligence, sd);
    }

    if (gender == GENDER_MALE) {
        mean = 70;
        mean -= abs((int)age - 18);
        secHardness = GetNormalDistributionUint(mean, 20);

        mean = 20;
        mean += abs((int)age - 40);
        secTimelen = GetNormalDistributionUint(mean, 20);
    }

    mean = 20;
    mean += age;
    secSkill = GetNormalDistributionUint(mean, 20);
}

