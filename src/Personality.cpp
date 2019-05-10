#include "Personality.h"
#include "globals.h"


Personality::Personality()
    : extraversion(0)
    , agreeableness(0)
    , conscientiousness(0)
    , openness(0)
    , neuroticism(0)
    , secDesire(0)
    , secDomorsub(0)
{

}

Personality::~Personality()
{

}

void Personality::RandomInitPersonality(GENDER_ENUM gender, unsigned int age)
{
    int mean = 0;
    unsigned int sd = 30;

    if (gender == GENDER_MALE) {
        mean -= 20;
    }
    else if (gender == GENDER_FEMALE) {
        mean += 20;
    }

    extraversion = GetNormalDistributionInt(mean, sd);

    mean = 0;
    if (gender == GENDER_MALE) {
        mean -= 20;
    }
    else if (gender == GENDER_FEMALE) {
        mean += 20;
    }
    agreeableness = GetNormalDistributionInt(mean, sd);

    mean = 0;
    if (gender == GENDER_MALE) {
        mean += 10;
    }
    else if (gender == GENDER_FEMALE) {
        mean -= 10;
    }
    conscientiousness = GetNormalDistributionInt(mean, sd);

    mean = 0;
    if (gender == GENDER_MALE) {
        mean += 10;
    }
    else if (gender == GENDER_FEMALE) {
        mean -= 10;
    }
    openness = GetNormalDistributionInt(mean, sd);

    mean = 0;
    if (gender == GENDER_MALE) {
        mean -= 30;
    }
    else if (gender == GENDER_FEMALE) {
        mean += 30;
    }
    neuroticism = GetNormalDistributionInt(mean, sd);

    mean = 60;
    if (gender == GENDER_FEMALE) {
        mean -= abs((int)age - 35);
    }
    else {
        mean -= abs((int)age - 18);
    }
    secDesire = GetNormalDistributionUint(mean, 20);

    mean = 0;
    mean += openness;
    mean -= agreeableness;
    secDomorsub = GetNormalDistributionInt(mean, sd);
}

