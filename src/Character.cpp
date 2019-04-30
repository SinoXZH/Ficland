#include "Character.h"

Character::Character(unsigned int id)
    : charaId(id)
    , charaAge(0)
    , charaGender(GENDER_UNKNOWN)
    , charaRace(RACE_UNKNOWN)
{

}

Character::~Character()
{

}

void Character::InitChara(TITLE_ENUM title, JOB_ENUM job, RACE_ENUM race, unsigned int age, GENDER_ENUM gender, unsigned int appranceScore)
{
    socialStatus.nobleTitle = title;
    socialStatus.job = job;
    
    unsigned int randNum = 0;

    if (race == RACE_UNKNOWN) {
        randNum = GetRandomNum(0, RACE_COUNT - 1);
        race = (RACE_ENUM)randNum;
    }
    charaRace = race;

    if (age == 0) {
        age = RandomInitAge(job);
    }
    charaAge = age;

    if (gender == GENDER_UNKNOWN) {
        gender = RandomInitGender(job);
    }

    charaGender = gender;

    if (appranceScore == 0) {
        appranceScore = RandomInitAppearanceScore();
    }

    appearance.RandomInitAppearance(charaRace, charaGender, charaAge, appranceScore);
    ability.RandomInitAbility(socialStatus.job);
    personality.RandomInitPersonality(gender);
}

unsigned int Character::RandomInitAge(JOB_ENUM job)
{
    unsigned int sd = 5;

    switch (job)
    {
    case JOB_LANDLORD:
        return GetNormalDistributionUnsignedNum(LANDLORD_EVERAGE_AGE, sd);
    case JOB_ACADEMY_PRESIDENT:
        return GetNormalDistributionUnsignedNum(PRESIDENT_EVERAGE_AGE, sd);
    case JOB_ACADEMY_TEACHER:
        return GetNormalDistributionUnsignedNum(TEACHER_EVERAGE_AGE, sd);
    case JOB_ACADEMY_STUDENT:
        return GetNormalDistributionUnsignedNum(STUDENT_EVERAGE_AGE, sd);
    default:
        break;
    }

    return 0;
}

GENDER_ENUM Character::RandomInitGender(JOB_ENUM job)
{
    unsigned int randNum = GetRandomNum(1,10);

    switch (job)
    {
    case JOB_LANDLORD:
        if (randNum == 1) {
            return GENDER_FEMALE;
        }
        break;
    case JOB_ACADEMY_PRESIDENT:
        if (randNum < 3) {
            return GENDER_FEMALE;
        }
        break;
    case JOB_ACADEMY_TEACHER:
        if (randNum < 8) {
            return GENDER_FEMALE;
        }
        break;
    case JOB_ACADEMY_STUDENT:
        if (randNum < 6) {
            return GENDER_FEMALE;
        }
        break;
    default:
        break;
    }

    return GENDER_MALE;
}

GENDER_ENUM Character::RandomInitGender()
{
    unsigned int randNum = GetRandomNum(0, 1);
    return (GENDER_ENUM)randNum;
}

unsigned int Character::RandomInitAppearanceScore()
{
    return 0;
}
