#include "XmlManager.h"


using namespace tinyxml2;

XmlManager::XmlManager()
{

}

XmlManager::~XmlManager()
{

}

bool XmlManager::CreateNewXml(const string& filepath)
{
    ofstream ofs;
    ofs.open(filepath.c_str(), ios_base::out);
    if (!ofs.is_open()) {
        return false;
    }

    ofs << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\r\n";
    ofs.close();
    xmlFilePath = filepath;
    return true;
}

bool XmlManager::LoadXml(const string& filepath)
{
    if (tinixml2Doc.LoadFile(filepath.c_str()) == tinyxml2::XML_SUCCESS) {
        xmlFilePath = filepath;
        return true;
    }

    return false;
}

void* XmlManager::CreateRoot(const string& tagName)
{
    XMLElement* element = tinixml2Doc.NewElement(tagName.c_str());
    return (void*)tinixml2Doc.LinkEndChild(element);
}

void* XmlManager::CreateChild(const void* parent, const string& tagName)
{
    XMLElement* parentEle = (XMLElement*)parent;
    XMLElement* childEle = tinixml2Doc.NewElement(tagName.c_str());
    return (void*)parentEle->LinkEndChild(childEle);
}

void* XmlManager::GetFirstChild(const void* parent, string childTag/* = ""*/)
{
    if (parent == NULL) {
        return NULL;
    }

    XMLElement* parentEle = (XMLElement*)parent;
    if (childTag.empty()) {
        return (void*)parentEle->FirstChild();
    }
    
    return (void*)parentEle->FirstChildElement(childTag.c_str());
}

void* XmlManager::GetNextNeighbor(const void* node)
{
    if (node == NULL) {
        return NULL;
    }

    XMLNode* xmlNode = (XMLNode*)node;
    XMLNode* next = xmlNode->NextSibling();
    return (void*)next;
}

bool XmlManager::SetAttribute(const void* node, const string& attrName, const string& attrValue)
{
    if (node == NULL) {
        return false;
    }

    if (attrName.empty()) {
        return false;
    }

    XMLElement* ele = (XMLElement*)node;
    ele->SetAttribute(attrName.c_str(), attrValue.c_str());
    return true;
}

bool XmlManager::SetAttribute(const void* node, const string& attrName, int attrValue)
{
    if (node == NULL) {
        return false;
    }

    if (attrName.empty()) {
        return false;
    }

    XMLElement* ele = (XMLElement*)node;
    ele->SetAttribute(attrName.c_str(), attrValue);
    return true;
}

string XmlManager::GetAttribute(const void* node, const string& attrName)
{
    if (node == NULL) {
        return "";
    }

    if (attrName.empty()) {
        return "";
    }

    XMLElement* ele = (XMLElement*)node;
    return ele->Attribute(attrName.c_str());
}

bool XmlManager::Save()
{
    return (tinixml2Doc.SaveFile(xmlFilePath.c_str()) == XML_SUCCESS);
}

void* XmlManager::GetRootNode()
{
    XMLElement* node = tinixml2Doc.FirstChildElement();
    return (void*)node;
}

string XmlManager::GetNodeTag(const void* node)
{
    if (node == NULL) {
        return "";
    }

    XMLElement* ele = (XMLElement*)node;
    return ele->Value();
}

