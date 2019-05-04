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
    virtual void RandomInitGroupMembers() {};

public:
    Character* leader;
    vector<Character*> memberList;
};


class Family : public Group{
public:
    virtual void SetGroupLeader(Character* chara);

    virtual void RandomInitGroupMembers();

protected:
    void RandomInitConcubines();

    void RandomInitChildren(Character* father, Character* mother);

public:
    string familyName;
    Character* husband;
    Character* wife;
    vector<Character*> concubines;
    vector<Character*> children;
    vector<Character*> slaves;
};

class AcademyGroup : public Group {
public:
    virtual void SetGroupLeader(Character* chara);

public:
    Character* president;
    vector<Character*> teacherList;
    vector<Character*> studentList;
};

#endif //__GROUP_H__

