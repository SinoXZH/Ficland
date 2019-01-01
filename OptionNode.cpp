#include "OptionNode.h"
#include <string>
#include <vector>
#include "GlobalDefine.h"
#include "utils.h"

using namespace std;

OptionNode::OptionNode(const string& name)
: parent(NULL)
{
    optionName = name;
}

OptionNode::~OptionNode()
{

}

int OptionNode::AddChild(const string& childName)
{
    OptionNode* child = new OptionNode(childName);

    childList.push_back(child);

    child->parent = this;

    return RET_SUCCESS;
}

int OptionNode::Process()
{
    return RET_SUCCESS;
}

OptionNode* OptionNode::Run()
{
    if (Process() != RET_SUCCESS)
    {
        return NULL;
    }

    Output(CHOOSE_OPTION);

    string optionList;
    for (vector<OptionNode*>::iterator iter = childList.begin(); iter != childList.end(); ++iter)
    {
        if (!optionList.empty())
        {
            optionList += ", ";
        }
        optionList += (*iter)->optionName;
        
    }

    Output(optionList);

    string input;

    while (true)
    {
        input = Input();
        for (vector<OptionNode*>::iterator iter = childList.begin(); iter != childList.end(); ++iter)
        {
            if (input.compare((*iter)->optionName) == 0)
            {
                return *iter;
            }
        }

        Output(INVALID_OPTION);
    }

    return NULL;
}
