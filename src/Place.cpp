#include "Place.h"

Place::Place()
    : owner(NULL)
    , functionalGroup(NULL)
{

}

Place::~Place()
{
    if (functionalGroup != NULL) {
        delete functionalGroup;
        functionalGroup = NULL;
    }
}

void House::Init(unsigned int lv)
{
    
}

