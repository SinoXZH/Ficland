#ifndef __APPEARANCE_H__
#define __APPEARANCE_H__


typedef enum {
    APP_UGLY,
    APP_NORMAL,
    APP_PRETTY,
    APP_FAIRY,
    APP_UNPARALLELED
}APPEARANCE_LEVEL;


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


class Appearance{
public:
    Appearance();
    ~Appearance();

protected:
    int prettyLevel;
    unsigned int hight;
    int strongLevel;
    int fatLevel;

    HAIR_COLOR hairColor;
    HAIR_STYLE hairStyle;
    
};

class FemaleAppearance : public Appearance{

};


#endif //__APPEARANCE_H__
