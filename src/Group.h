#ifndef __GROUP_H__
#define __GROUP_H__


#include "globals.h"
#include "Character.h"


class Group {
public:
    Group();
    virtual ~Group();

public:
    virtual void SetGroupLeader(Character* chara) = 0;
    virtual void RandomInitGroupMembers() = 0;

public:

    Character* leader;
    vector<Character*> memberList;
};


class Family : public Group{
public:
    virtual void SetGroupLeader(Character* chara);

    virtual void RandomInitGroupMembers();

public:
    Character* husband;
    Character* wife;
    vector<Character*> concubines;
    vector<Character*> children;
    vector<Character*> slaves;
};

#endif //__GROUP_H__

