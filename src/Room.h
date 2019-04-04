#ifndef __ROOM_H__
#define __ROOM_H__


#include "globals.h"
#include "Character.h"

class Room {
public:
    Room();
    ~Room();

protected:
    string roomName;
    list<Character*> locateCharList;
};


#endif //__ROOM_H__
