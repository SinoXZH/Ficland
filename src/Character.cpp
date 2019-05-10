#include "Character.h"
#include "TextManager.h"

Character::Character(unsigned int id)
    : charaId(id)
    , charaAge(0)
    , charaGender(GENDER_UNKNOWN)
    , charaRace(RACE_UNKNOWN)
    , charaSpouse(NULL)
    , charaFather(NULL)
    , charaMother(NULL)
{

}

Character::~Character()
{

}

void Character::InitChara(const string& houseName, TITLE_ENUM title, JOB_ENUM job, unsigned int statusScore, 
RACE_ENUM race, unsigned int age, GENDER_ENUM gender, int appranceScore)
{
    if (houseName.empty()) {
        familyName = TextManager::GetInstance()->GetRandomOrientalFamilyName();
    } else {
        familyName = houseName;
    }

    socialStatus.nobleTitle = title;
    socialStatus.job = job;

    if (statusScore == 0) {
        socialStatus.GenerateStatusScoreFromTitleAndJob();
    }
    else {
        socialStatus.statusScore = statusScore;
    }
    
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
    ability.RandomInitAbility(socialStatus, age, charaGender);
    personality.RandomInitPersonality(gender, age);
}

unsigned int Character::RandomInitAge(JOB_ENUM job)
{
    unsigned int sd = 3;

    switch (job)
    {
    case JOB_LANDLORD:
        return GetNormalDistributionUint(LANDLORD_EVERAGE_AGE, sd);
    case JOB_HOSPITAL_PRESIDENT:
        return GetNormalDistributionUint(PRESIDENT_EVERAGE_AGE, sd);
    case JOB_HOSPITAL_DOCTOR:
        return GetNormalDistributionUint(DOCTOR_EVERAGE_AGE, sd);
    case JOB_HOSPITAL_NURSE:
        return GetNormalDistributionUint(NURSE_EVERAGE_AGE, sd);
    case JOB_ACADEMY_PRESIDENT:
        return GetNormalDistributionUint(PRESIDENT_EVERAGE_AGE, sd);
    case JOB_ACADEMY_MAGIC_TEACHER:
    case JOB_ACADEMY_FIGHTER_TEACHER:
    case JOB_ACADEMY_ARCHER_TEACHER:
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
    unsigned int randNum = GetRandomUint(0, 9);

    switch (job)
    {
    case JOB_LANDLORD:
        if (randNum == 0) {
            return GENDER_FEMALE;
        }
        break;
    case JOB_HOSPITAL_PRESIDENT:
        if (randNum < 6) {
            return GENDER_FEMALE;
        }
        break;
    case JOB_HOSPITAL_DOCTOR:
        if (randNum < 8) {
            return GENDER_FEMALE;
        }
        break;
    case JOB_HOSPITAL_NURSE:
        return GENDER_FEMALE;
        break;
    case JOB_ACADEMY_PRESIDENT:
        if (randNum < 3) {
            return GENDER_FEMALE;
        }
        break;
    case JOB_ACADEMY_MAGIC_TEACHER:
        if (randNum < 8) {
            return GENDER_FEMALE;
        }
        break;
    case JOB_ACADEMY_FIGHTER_TEACHER:
        if (randNum < 3) {
            return GENDER_FEMALE;
        }
    case JOB_ACADEMY_ARCHER_TEACHER:
        if (randNum < 6) {
            return GENDER_FEMALE;
        }
        break;
    case JOB_ACADEMY_STUDENT:
        if (randNum < 5) {
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

    randMean += socialStatus.statusScore;
    if (socialStatus.job == JOB_CONCUBINE) {
        randMean += 50;
    }
    else if (socialStatus.job == JOB_HOSPITAL_NURSE) {
        randMean += 30;
    }
    else if (socialStatus.job == JOB_ACADEMY_MAGIC_TEACHER
        || socialStatus.job == JOB_ACADEMY_FIGHTER_TEACHER
        || socialStatus.job == JOB_ACADEMY_ARCHER_TEACHER
        || socialStatus.job == JOB_HOSPITAL_DOCTOR) {
        randMean += 20;
    }

    return GetNormalDistributionInt(randMean, randsd);
}
