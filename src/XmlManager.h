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

    void* GetNextNeighbor(const void* node);

    bool SetAttribute(const void* node, const string& attrName, const string& attrValue);

    bool SetAttribute(const void* node, const string& attrName, int attrValue);

    string GetAttribute(const void* node, const string& attrName);

    int GetAttributeNum(const void* node, const string& attrName) { return atoi(GetAttribute(node, attrName).c_str()); }

    void* GetRootNode();

    string GetNodeTag(const void* node);

    bool Save();

protected:
    tinyxml2::XMLDocument tinixml2Doc;

    string xmlFilePath;
};


#endif

