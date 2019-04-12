#ifndef __GROUP_H__
#define __GROUP_H__


#include "globals.h"
#include "Character.h"


class Group {
public:
    Group();
    ~Group();

protected:

    Character* leader;
    vector<Character*> memberList;
};

#endif //__GROUP_H__

