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
    PLACE_ARENA,
    PLACE_MERCENARY_UNION,
    PLACE_ENUM_COUNT
}PLACE_ENUM;


class Place {
public:
    Place();
    ~Place();

protected:
    string placeName;
    vector<Room*> roomList;

    Character* owner;

    Group* functionalGroup;
};


class LoadMansion : public Place {
public:

protected:
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

class Arena : public Place {
public:

protected:
};

class MercenaryUnion : public Place {
public:

protected:
};

class Mansion : public Place {
public:

protected:
};

class Bungalow : public Place {
public:

protected:
};


#endif //__PLACE_H__
