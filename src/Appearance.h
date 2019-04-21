#ifndef __APPEARANCE_H__
#define __APPEARANCE_H__


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
    HAIR_BLACK,
    HAIR_BLOND,
    HAIR_BROWN,
    HAIR_RED,
    HAIR_SILVER,
    HAIR_GREY
}HAIR_COLOR;

typedef enum {
    HAIR_SHORT_CUT,
    HAIR_PASS_EAR,
    HAIR_OVER_SHOWDER,
    HAIR_HORSE_TAIL,
    HAIR_GIRL_BRAID,
    HAIR_WOMAN_BUN,
    HAIR_NOBLE_LADY
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
    int prettyLevel;
    unsigned int hight;
    int strongLevel;
    int fatLevel;
    int legLength;
    SKIN_COLOR skinColor;

    HAIR_COLOR hairColor;
    HAIR_STYLE hairStyle;
    EYE_COLOR eyeColor;
    EAR_STYLE earStyle;
    int eyeDepth;
    int noseBridgeSize;
    int noseWingSize;
    int mouthWidth;
    int lipsThickness;
    int faceLength;
    int faceWidth;

    //male
    BEARD_ENUM beard;

    //female
    int xSize;
    int xRaise;
    int tSize;
    int tRaise;
    int waistSize;
    int skinSmooth;
};


#endif //__APPEARANCE_H__
