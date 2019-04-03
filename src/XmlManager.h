#ifndef __XML_MANAGER_H__
#define __XML_MANAGER_H__

#include "tinyxml2.h"


class XmlManager {
public:
    XmlManager();
    ~XmlManager();

protected:
    tinyxml2::XMLDocument tinixml2Doc;
};


#endif

