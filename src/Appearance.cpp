#include "Appearance.h"


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
    , strongLevel(0)
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

void Appearance::RandomInitAppearance(RACE_ENUM race, GENDER_ENUM gender, unsigned int age, unsigned int score)
{

}

