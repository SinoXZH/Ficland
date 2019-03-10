#include "globals.h"
#include "FicApp.h"


FicApp::FicApp()
{

}

FicApp::~FicApp()
{

}

bool FicApp::Init()
{
    Archive::arcRootDir = GetAppDir();
    Archive::arcRootDir = Archive::arcRootDir.substr(0, Archive::arcRootDir.find_last_of('/'));
    Archive::arcRootDir += "/archive";
    string info = "Archive directory: ";
    info += Archive::arcRootDir;
    PrintInfo(info);
    return true;
}

bool FicApp::Run()
{
    Output("Welcome to Ficland!");
    
    vector<string> cmdList;
    cmdList.push_back("quit");
    cmdList.push_back("new");
    cmdList.push_back("load");
    cmdList.push_back("design");

    while (true) {
        
        OutputCmdList(cmdList);
        string input = InputCmdList(cmdList);

        if (input == "quit"){
            return true;
        }else if (input == "new"){

        }else if (input == "load"){
            
        }else if (input == "design"){
            if (Design() == false){
                return false;
            }
        }else{
            PrintErr("unknown input.");
        }
    }

    return true;
}

bool FicApp::Design()
{
    Output("Now we design the world.");

    curArchive.arcDir = Archive::arcRootDir += "/base";

    vector<string> cmdList;
    cmdList.push_back("quit");
    cmdList.push_back("create new empty matrix file");
    
    while (true) {
        
        OutputCmdList(cmdList);
        string input = InputCmdList(cmdList);

        if (input == "quit"){
            return true;
        }else if (input == "create new empty matrix file"){
            if (CreateNewEmptyMatrixFile() == false){
                return false;
            }
        }else{
            PrintErr("unknown input.");
        }
    }
    
    return true;
}

bool FicApp::CreateNewEmptyMatrixFile()
{
    Output("Please input empty file name:");
    string input = Input();
    return curArchive.CreateNewEmptyMatrixFile(input);
}
