#ifndef __PLACE_H__
#define __PLACE_H__

#include "globals.h"
#include "Room.h"

class Place {
public:
    Place();
    ~Place();

protected:
    string placeName;
    vector<Room*> roomList;
};


#endif //__PLACE_H__
