#ifndef __APPEARANCE_H__
#define __APPEARANCE_H__

#include "CharaDefine.h"

typedef enum {
    SKIN_PURE_WHITE,
    SKIN_MILK_WHITE,
    SKIN_PALE_WHITE,
    SKIN_WHEAT,
    SKIN_BROWN,
    SKIN_DARK,
    SKIN_LIGHT_BLUE
}SKIN_COLOR;

typedef enum {
    HAIR_COLOR_BLACK,
    HAIR_COLOR_BLOND,
    HAIR_COLOR_BROWN,
    HAIR_COLOR_RED,
    HAIR_COLOR_SILVER,
    HAIR_COLOR_GREY
}HAIR_COLOR;

typedef enum {
    HAIR_STYLE_BALD,
    HAIR_STYLE_SHORT_CUT,
    HAIR_STYLE_PASS_EAR,
    HAIR_STYLE_OVER_SHOWDER,
    HAIR_STYLE_HORSE_TAIL,
    HAIR_STYLE_GIRL_BRAID,
    HAIR_STYLE_WOMAN_BUN,
    HAIR_STYLE_NOBLE_LADY
}HAIR_STYLE;

typedef enum {
    EYE_BLACK,
    EYE_BROWN,
    EYE_BLUE,
    EYE_GRAY,
    EYE_RED,
    EYE_GOLDEN,
    EYE_GREEN,
}EYE_COLOR;

typedef enum {
    EAR_NORMAL,
    EAR_ELVISH,
    EAR_DEVEL
}EAR_STYLE;

typedef enum {
    BEARD_NONE,
    BEARD_MOUSTACHE,
    BEARD_GOATEE,
    BEARD_WHISKERS,
    BEARD_FULL
}BEARD_ENUM;

class Appearance{
public:
    Appearance();
    ~Appearance();

public:
    void RandomInitAppearance(RACE_ENUM race, GENDER_ENUM gender, unsigned int age, unsigned int score);

public:
    int prettyLevel;
    int fitnessLevel;
    unsigned int hight;
    int fatLevel;
    int legLength;
    SKIN_COLOR skinColor;

    HAIR_COLOR hairColor;
    HAIR_STYLE hairStyle;
    EYE_COLOR eyeColor;
    int eyeSize;
    int eyeDepth;
    EAR_STYLE earStyle;
    
    int noseBridgeSize;
    int noseWingSize;
    int mouthWidth;
    int lipsThickness;
    int faceLength;
    int faceWidth;

    //male
    BEARD_ENUM beard;
    int strongLevel;

    //female
    int xSize;
    int xRaise;
    int xtSize;
    int xtDarkness;
    int tSize;
    int tRaise;
    int waistSize;
    int skinSmooth;
};


#endif //__APPEARANCE_H__
