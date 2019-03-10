#include "FicApp.h"

int main()
{
    FicApp app;
    if (app.Init() == false){
        return -1;
    }

    if (app.Run() == false){
        return -1;
    }

    return 0;
}
