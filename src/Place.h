#ifndef __PLACE_H__
#define __PLACE_H__

#include "globals.h"
#include "Room.h"
#include "Group.h"


typedef enum {
    PLACE_LORD_MANSION,
    PLACE_GOV_OFFICE,
    PLACE_POLICE_OFFICE,
    PLACE_MILITARY_CAMP,
    PLACE_MARKET,
    PLACE_TAVERN,
    PLACE_AUCTION_HOUSE,
    PLACE_ACADEMY,
    PLACE_HOSPITAL,
    PLACE_ENUM_COUNT
}PLACE_ENUM;


class Place {
public:
    Place();
    virtual ~Place();

public:
    string placeName;
    vector<Room*> roomList;

    Character* owner;

    Group* functionalGroup;
};


class GovOffice : public Place {
public:

protected:
};

class PoliceOffice : public Place {
public:

protected:
};

class MillitaryCamp : public Place {
public:

protected:
};

class Market : public Place {
public:

protected:
};

class Tavern : public Place {
public:

protected:
};

class AuctionHouse : public Place {
public:

protected:
};

class Academy : public Place {
public:

protected:
};

class Hospital : public Place {
public:

protected:
};

typedef enum{
    HOUSE_NORMAL = 0,
    HOUSE_VILLA,
    HOUSE_MANSION,
    HOUSE_PALACE
}HOUSE_LEVEL;

class House : public Place {
public:
    void Init(unsigned int lv);

protected:
    HOUSE_LEVEL level;
};


#endif //__PLACE_H__
