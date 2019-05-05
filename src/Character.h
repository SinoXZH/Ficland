#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "globals.h"
#include "Appearance.h"
#include "Personality.h"
#include "Ability.h"
#include "SocialStatus.h"
#include "Relationship.h"


class Character {
public:
    Character(unsigned int id);
    ~Character();

public:

    void InitChara(
        const string& houseName = "",
        TITLE_ENUM title = TITLE_NONE,
        JOB_ENUM job = JOB_NONE, 
        RACE_ENUM race = RACE_UNKNOWN, 
        unsigned int age = 0, 
        GENDER_ENUM gender = GENDER_UNKNOWN
        , int appranceScore = 0);

public:
    static GENDER_ENUM RandomInitGender();

protected:
    unsigned int RandomInitAge(JOB_ENUM job);
    GENDER_ENUM RandomInitGender(JOB_ENUM job);

    int RandomInitAppearanceScore();

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

    map<unsigned int, Relationship> relatedCharaMap;
};

#endif //__CHARACTER_H__

