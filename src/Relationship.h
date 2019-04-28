#ifndef __RELATIONSHIP_H__
#define __RELATIONSHIP_H__


typedef enum {
    RELATION_SPOUSE,
    RELATION_DEPENDENT_SPOUSE,
    RELATION_PARENT,
    RELATION_CHILD,
    RELATION_MASTER,
    RELATION_SLAVE,
    RELATION_LEADER,
    RELATION_SUBORDINATE
}RELATION_TYPE;


class Relationship {
public:
    Relationship();
    ~Relationship();

public:
    RELATION_TYPE relationType;
};


#endif //__RELATIONSHIP_H__
