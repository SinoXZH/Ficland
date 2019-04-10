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
    Archive::arcRootDir = Archive::arcRootDir.substr(0, Archive::arcRootDir.find_last_of(PATH_SEPARATOR));
    Archive::arcRootDir += PATH_SEPARATOR;
    Archive::arcRootDir += "archive";
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

    curArchive.arcDir = Archive::arcRootDir + PATH_SEPARATOR;
    curArchive.arcDir += "base";

    vector<string> cmdList;
    cmdList.push_back("quit");
    cmdList.push_back("create new empty matrix file");
    cmdList.push_back("load matrix file");
    cmdList.push_back("save archive to xml");
    cmdList.push_back("load xml to archive");
    
    while (true) {
        
        OutputCmdList(cmdList);
        string input = InputCmdList(cmdList);

        if (input == "quit"){
            return true;
        }else if (input == "create new empty matrix file"){
            if (CreateNewEmptyMatrixFile() == false){
                return false;
            }
        }else if (input == "load matrix file") {
            if (LoadMatrixFile() == false) {
                return false;
            }
        }
        else if (input == "save archive to xml") {
            if (SaveArchiveToXml() == false) {
                return false;
            }
        }
        else if (input == "load xml to archive") {
            if (LoadXmlToArchive() == false) {
                return false;
            }
        }
        else{
            PrintErr("unknown input.");
        }
    }
    
    return true;
}

bool FicApp::CreateNewEmptyMatrixFile()
{
    Output("Please input empty file name:");
    string fileName = Input();
    fileName += ".csv";
    Output("Please input matrix width:");
    int w = InputUint();
    Output("Please input matrix height:");
    int h = InputUint();
    return curArchive.CreateNewEmptyMatrixFile(fileName, w, h);
}

bool FicApp::LoadMatrixFile()
{
    Output("Please input file name:");
    string fileName = Input();
    fileName += ".csv";
    return curArchive.LoadMatrixFile(fileName);
}

bool FicApp::SaveArchiveToXml()
{
    return curArchive.SaveArchiveToXml();
}

bool FicApp::LoadXmlToArchive()
{
    return curArchive.LoadXmlToArchive();
}

