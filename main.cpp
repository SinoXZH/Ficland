#include "FicLandApp.h"

int main()
{
    int ret = 0;

    FicApp app;
    ret = app.Init();
    if (ret != 0)
    {
        return -1;
    }

    while (true)
    {
        ret = app.Run();
        if (ret == 1)
        {
            break;
        }
        else if (ret != 0)
        {
            return -1;
        }
    }

    return 0;
}