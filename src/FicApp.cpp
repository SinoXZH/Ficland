#include "FicApp.h"
#include "globals.h"

FicApp::FicApp()
{

}

FicApp::~FicApp()
{

}

bool FicApp::Init()
{
    return true;
}

bool FicApp::Run()
{
    Output("Welcome to Ficland!");
    
    while (true) {
        Output("Please choose options below:");
        Output("new load design quit");

        string input = Input();

        if (input == "quit"){
            return true;
        }else if (input == "new"){

        }else if (input == "load"){
            
        }else if (input == "design"){

        }else{
            PrintErr("unknown input.");
        }
    }

    return true;
}
