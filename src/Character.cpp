#include "Character.h"
#include "TextManager.h"

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

void Character::InitChara(const string& houseName, TITLE_ENUM title, JOB_ENUM job, 
RACE_ENUM race, unsigned int age, GENDER_ENUM gender, int appranceScore)
{
    if (houseName.empty()) {
        familyName = TextManager::GetInstance()->GetRandomOrientalFamilyName();
    } else {
        familyName = houseName;
    }

    socialStatus.nobleTitle = title;
    socialStatus.job = job;
    
    unsigned int randNum = 0;

    if (race == RACE_UNKNOWN) {
        randNum = GetRandomUint(0, RACE_COUNT - 1);
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

    selfName = TextManager::GetInstance()->GetRandomOrientalName(charaGender);

    if (appranceScore == 0) {
        appranceScore = RandomInitAppearanceScore();
    }

    appearance.RandomInitAppearance(charaRace, charaGender, charaAge, appranceScore);
    ability.RandomInitAbility(socialStatus.job);
    personality.RandomInitPersonality(gender);
}

unsigned int Character::RandomInitAge(JOB_ENUM job)
{
    unsigned int sd = 3;

    switch (job)
    {
    case JOB_LANDLORD:
        return GetNormalDistributionUint(LANDLORD_EVERAGE_AGE, sd);
    case JOB_ACADEMY_PRESIDENT:
        return GetNormalDistributionUint(PRESIDENT_EVERAGE_AGE, sd);
    case JOB_ACADEMY_TEACHER:
        return GetNormalDistributionUint(TEACHER_EVERAGE_AGE, sd);
    case JOB_ACADEMY_STUDENT:
        return GetNormalDistributionUint(STUDENT_EVERAGE_AGE, sd);
    default:
        break;
    }

    return 0;
}

GENDER_ENUM Character::RandomInitGender(JOB_ENUM job)
{
    unsigned int randNum = GetRandomUint(1,10);

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
    unsigned int randNum = GetRandomUint(0, 1);
    return (GENDER_ENUM)randNum;
}

int Character::RandomInitAppearanceScore()
{
    int randMean = 0;
    unsigned int randsd = 20;

    randMean += (10 * (unsigned int)socialStatus.nobleTitle);
    if (socialStatus.job == JOB_CONCUBINE) {
        randMean += 50;
    }
    else if (socialStatus.job == JOB_ACADEMY_TEACHER) {
        randMean += 20;
    }

    return GetNormalDistributionInt(randMean, randsd);
}
