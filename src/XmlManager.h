#ifndef __XML_MANAGER_H__
#define __XML_MANAGER_H__

#include "globals.h"
#include "tinyxml2.h"


class XmlManager {
public:
    XmlManager();
    ~XmlManager();

public:
    bool CreateNewXml(const string& filepath);

    bool LoadXml(const string& filepath);

    void* CreateRoot(const string& tagName);

    void* CreateChild(const void* parent, const string& tagName);

    void* GetFirstChild(const void* parent, string childTag = "");

    bool SetAttribute(const void* node, const string& attrName, const string& attrValue);

    bool SetAttribute(const void* node, const string& attrName, unsigned int attrValue);

    string GetAttribute(const void* node, const string& attrName);

    bool Save();

protected:
    tinyxml2::XMLDocument tinixml2Doc;

    string xmlFilePath;
};


#endif

