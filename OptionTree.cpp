#include "OptionTree.h"
#include "OptionDefine.h"
#include "GlobalDefine.h"


OptionTree::OptionTree()
: root(NULL),
  curNode(NULL)
{

}

OptionTree::~OptionTree()
{
    
}

int OptionTree::Init()
{
    root = new OptionNode(OPTION_ROOT);

    root->AddChild(OPTION_NEW);
    root->AddChild(OPTION_LOAD);
    root->AddChild(OPTION_DESIGN);
    root->AddChild(OPTION_OPTION);
    root->AddChild(OPTION_QUIT);

    curNode = root;

    return RET_SUCCESS;
}

void OptionTree::Run()
{
    while (curNode)
    {
        curNode = curNode->Run();
    }
}
