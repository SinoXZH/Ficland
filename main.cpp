#include "FicLandApp.h"
#include "GlobalDefine.h"

int main()
{
    int ret = 0;

    FicApp app;
    ret = app.Init();
    if (ret != RET_SUCCESS)
    {
        return APP_ERR_EXIT;
    }

    while (true)
    {
        ret = app.Run();
        if (ret == RET_EXIT)
        {
            break;
        }
        else if (ret != RET_SUCCESS)
        {
            return APP_ERR_EXIT;
        }
    }

    return APP_SUCC_EXIT;
}