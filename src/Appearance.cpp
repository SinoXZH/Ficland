#include "Appearance.h"
#include "globals.h"


Appearance::Appearance()
    : prettyLevel(0)
    , fitnessLevel(0)
    , hight(0)
    , fatLevel(0)
    , legLength(0)
    , skinColor(SKIN_PURE_WHITE)
    , hairColor(HAIR_COLOR_BLACK)
    , hairStyle(HAIR_STYLE_BALD)
    , eyeColor(EYE_BLACK)
    , eyeSize(0)
    , eyeDepth(0)
    , earStyle(EAR_NORMAL)
    , noseBridgeSize(0)
    , noseWingSize(0)
    , mouthWidth(0)
    , lipsThickness(0)
    , faceLength(0)
    , faceWidth(0)
    , beard(BEARD_NONE)
    , ckSize(0)
    , xSize(0)
    , xRaise(0)
    , xtSize(0)
    , xtDarkness(0)
    , tSize(0)
    , tRaise(0)
    , waistSize(0)
    , skinSmooth(0)
{

}

Appearance::~Appearance()
{
    
}

void Appearance::RandomInitAppearance(RACE_ENUM race, GENDER_ENUM gender, unsigned int age, int score)
{
    prettyLevel = GetNormalDistributionInt(score, 10);
    if (prettyLevel == 0) {
        ++prettyLevel;
    }
    fitnessLevel = 2 * score - prettyLevel;
    if (fitnessLevel == 0) {
        ++fitnessLevel;
    }

    //hight
    int mean = 173;
    unsigned int sd = 10;
    if (gender == GENDER_FEMALE) {
        mean -= 10;
    }
    mean += (int)(fitnessLevel / 10);
    sd -= (int)(fitnessLevel / 10);
    hight = GetNormalDistributionUint(mean, sd);

    //fat
    mean = 0;
    sd = 30;
    sd -= (int)(fitnessLevel / 5);
    fatLevel = GetNormalDistributionInt(mean, sd);

    //leglength
    mean = fitnessLevel;
    sd = 10;
    legLength = GetNormalDistributionInt(mean, sd);

    //skin color
    if (score > 20) {
        skinColor = SKIN_MILK_WHITE;
    }
    else if (score < -20) {
        skinColor = SKIN_BROWN;
    }
    else {
        skinColor = SKIN_WHEAT;
    }

    //hair color
    hairColor = HAIR_COLOR_BLACK;

    //hair style
    if (gender == GENDER_MALE) {
        if (age < 30) {
            hairStyle = (HAIR_STYLE)GetRandomUint(HAIR_STYLE_SHORT_CUT, HAIR_STYLE_HORSE_TAIL);
        }
        else {
            hairStyle = (HAIR_STYLE)GetRandomUint(HAIR_STYLE_BALD, HAIR_STYLE_SHORT_CUT);
        }
    }
    else {
        if (age < 25) {
            hairStyle = (HAIR_STYLE)GetRandomUint(HAIR_STYLE_HORSE_TAIL, HAIR_STYLE_OVER_SHOWDER);
        }
        else {
            hairStyle = (HAIR_STYLE)GetRandomUint(HAIR_STYLE_PASS_EAR, HAIR_STYLE_NOBLE_LADY);
        }
    }

    //eyeColor
    eyeColor = EYE_BLACK;

    //eyeSize
    mean = prettyLevel;
    sd = 10;
    eyeSize = GetNormalDistributionInt(mean, sd);

    //eyeDepth
    mean = 0;
    sd = 5;
    eyeDepth = GetNormalDistributionInt(mean, sd);

    //earStyle
    earStyle = EAR_NORMAL;

    //noseBridgeSize
    mean = prettyLevel / 5;
    sd = 10;
    noseBridgeSize = GetNormalDistributionInt(mean, sd);

    //noseWingSize
    mean = - prettyLevel / 5;
    sd = 10;
    noseWingSize = GetNormalDistributionInt(mean, sd);

    //mouthWidth
    mean = 0;
    sd = (unsigned int)abs(100 / prettyLevel);
    mouthWidth = GetNormalDistributionInt(mean, sd);

    //lipsThickness
    mean = 0;
    sd = (unsigned int)abs(100 / prettyLevel);
    lipsThickness = GetNormalDistributionInt(mean, sd);

    //faceLength
    mean = 0;
    sd = (unsigned int)abs(100 / prettyLevel);
    faceLength = GetNormalDistributionInt(mean, sd);

    //faceWidth
    mean = -prettyLevel;
    sd = 5;
    faceWidth = GetNormalDistributionInt(mean, sd);

    if (gender == GENDER_MALE) {
        //beard
        if (age < 30) {
            beard = (BEARD_ENUM)GetRandomUint(BEARD_NONE, BEARD_MOUSTACHE);
        }
        else {
            beard = (BEARD_ENUM)GetRandomUint(BEARD_MOUSTACHE, BEARD_FULL);
        }

        ckSize = GetNormalDistributionUint(10, 3);
    }
    else if (gender == GENDER_FEMALE) {
        //xSize
        mean = fitnessLevel + age;
        sd = 10;
        xSize = GetNormalDistributionUint(mean, sd);

        //xRaise
        mean = fitnessLevel + 30 - age;
        sd = 10;
        xRaise = GetNormalDistributionInt(mean, sd);

        //xtSize
        mean = age;
        sd = 10;
        xtSize = GetNormalDistributionUint(mean, sd);

        //xtDarkness
        mean = age;
        sd = 10;
        xtDarkness = GetNormalDistributionUint(mean, sd);

        //tSize
        mean = fitnessLevel + age;
        sd = 10;
        tSize = GetNormalDistributionUint(mean, sd);

        //tRaise
        mean = fitnessLevel + 30 - age;
        sd = 10;
        tRaise = GetNormalDistributionInt(mean, sd);

        //waistSize
        mean = fatLevel - fitnessLevel;
        sd = 10;
        waistSize = GetNormalDistributionInt(mean, sd);

        //skin smooth
        mean = score + 30 - age;
        sd = 10;
        skinSmooth = GetNormalDistributionInt(mean, sd);
    }
}

