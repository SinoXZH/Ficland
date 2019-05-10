#ifndef __PERSONALITY_H__
#define __PERSONALITY_H__


#include "CharaDefine.h"


class Personality{
public:
    Personality();
    ~Personality();

public:
    void RandomInitPersonality(GENDER_ENUM gender, unsigned int age);

public:
    int extraversion;
    int agreeableness;
    int conscientiousness;
    int openness;
    int neuroticism;

    unsigned int secDesire;
    int secDomorsub;
};

#endif //__PERSONALITY_H__