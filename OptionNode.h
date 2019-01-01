#ifndef __OPTION_NODE_H__
#define __OPTION_NODE_H__

#include <string>
#include <vector>

using namespace std;


class OptionNode{
public:
    OptionNode(const string& name);
    ~OptionNode();

    int AddChild(const string& childName);

    virtual int Process();

    OptionNode* Run();

protected:
    string optionName;

    OptionNode* parent;

    vector<OptionNode*> childList;
};

#endif //__OPTION_NODE_H__