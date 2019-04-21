#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "globals.h"
#include "Appearance.h"
#include "Personality.h"
#include "Ability.h"
#include "SocialStatus.h"
#include "Relationship.h"


typedef enum{
    RACE_UNKNOWN = -1,
    RACE_HUMAN_SINIAN = 0,
    RACE_HUMAN_JAPIAN,
    RACE_HUMAN_NORDIAN,
    RACE_HUMAN_TICIAN,
    RACE_HUMAN_ROSSIAN,
    RACE_HUMAN_TARTAIN,
    RACE_ELF_LIGHT,
    RACE_ELF_DARK,
    RACE_DEOR_DEVERN,
    RACE_DEOR_DEVIA,
    RACE_COUNT
}RACE_ENUM;

typedef enum{
    GENDER_UNKNOWN = -1,
    GENDER_MALE = 0,
    GENDER_FEMALE
}GENDER_ENUM;

const unsigned int LANDLORD_EVERAGE_AGE = 40;
const unsigned int PRESIDENT_EVERAGE_AGE = 40;
const unsigned int TEACHER_EVERAGE_AGE = 30;
const unsigned int STUDENT_EVERAGE_AGE = 18;

class Character {
public:
    Character(unsigned int id);
    ~Character();

public:

    void InitChara(
        TITLE_ENUM title = TITLE_NONE,
        JOB_ENUM job = JOB_NONE, 
        RACE_ENUM race = RACE_UNKNOWN, 
        unsigned int age = 0, 
        GENDER_ENUM gender = GENDER_UNKNOWN);

protected:
    unsigned int RandomInitAge(JOB_ENUM job);
    GENDER_ENUM RandomInitGender(JOB_ENUM job);

public:
    unsigned int charaId;
    unsigned int charaAge;
    string familyName;
    string selfName;
    GENDER_ENUM charaGender;
    RACE_ENUM charaRace;
    
    Appearance appearance;
    SocialStatus socialStatus;
    Personality personality;
    Ability ability;
    map<unsigned int, Relationship> relationList;
};

#endif //__CHARACTER_H__

