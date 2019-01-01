#include "FicLandApp.h"
#include "GlobalDefine.h"
#include "utils.h"


FicApp::FicApp()
{

}

FicApp::~FicApp()
{

}

int FicApp::Init()
{
    Output(SPLIT_LINE);
    Output(WELCOME);
    Output(SPLIT_LINE);

    int ret = RET_SUCCESS;

    ret = optionTree.Init();
    if (ret != RET_SUCCESS)
    {
        return ret;
    }

    return ret;
}

int FicApp::Run()
{
    optionTree.Run();

    return RET_EXIT;
}

