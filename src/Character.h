#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "globals.h"
#include "Appearance.h"
#include "Personality.h"
#include "Ability.h"
#include "Relationship.h"


typedef enum{
    RACE_HUMAN_SINIAN,
    RACE_HUMAN_TICIAN,
    RACE_HUMAN_TARTAIN,
    RACE_ELF_LIGHT,
    RACE_ELF_DARK,
    RACE_DEOR_DEVERN,
    RACE_DEOR_DEVIA
}RACE_ENUM;

typedef enum{
    GENDER_MALE,
    GENDER_FEMALE
}GENDER_ENUM;


class Character {
public:
    Character();
    ~Character();

protected:
    unsigned int charId;
    string familyName;
    string selfName;
    GENDER_ENUM gender;
    
    Appearance appearance;
    Personality personality;
    Ability ability;
    map<unsigned int, Relationship> relationList;
};

#endif //__CHARACTER_H__

