#ifndef __ROOM_H__
#define __ROOM_H__


#include "globals.h"
#include "Character.h"

class Room {
public:
    Room();
    ~Room();

protected:
    string name;
    list<Character*> locateCharList;
};

class Hall : public Room {
public:

protected:

};

class Square : public Room {
public:

protected:

};

class Office : public Room {
public:

protected:

};

class Camp : public Room {
public:

protected:

};

class LivingRoom : public Room {
public:

protected:

};

class BathRoom : public Room {
public:

protected:

};

class Kitchen : public Room {
public:

protected:

};

class Bedroom : public Room {
public:

protected:

};


#endif //__ROOM_H__
