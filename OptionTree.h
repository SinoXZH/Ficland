#ifndef __OPTION_TREE_H__
#define __OPTION_TREE_H__

#include "OptionNode.h"

class OptionTree{
public:
    OptionTree();
    ~OptionTree();

    int Init();

    void Run();

protected:

private:
    OptionNode* root;
    OptionNode* curNode;
};


#endif //__OPTION_TREE_H__
