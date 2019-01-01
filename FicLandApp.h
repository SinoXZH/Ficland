#ifndef __FICLAND_APP_H__
#define __FICLAND_APP_H__

#include "OptionTree.h"

class FicApp
{
public:
    FicApp();
    ~FicApp();

    int Init();
    int Run();

protected:

private:
    OptionTree optionTree;
};

#endif //__FICLAND_APP_H__
