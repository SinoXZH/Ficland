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
    GovOffice() { placeName = "Government Office"; }
protected:
};

class PoliceOffice : public Place {
public:
    PoliceOffice() { placeName = "Police Office"; }
protected:
};

class MillitaryCamp : public Place {
public:
    MillitaryCamp() { placeName = "Military Camp"; }
protected:
};

class Market : public Place {
public:
    Market() { placeName = "Market"; }
protected:
};

class Tavern : public Place {
public:
    Tavern() { placeName = "Tavern"; }
protected:
};

class AuctionHouse : public Place {
public:
    AuctionHouse() { placeName = "Auction House"; }
protected:
};

class Academy : public Place {
public:
    Academy() { placeName = "Academy"; }
protected:
};

class Hospital : public Place {
public:
    Hospital() { placeName = "Hospital"; }
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
    House() { placeName = "House"; }
    
    void Init(unsigned int lv);

protected:
    HOUSE_LEVEL level;
};


#endif //__PLACE_H__
