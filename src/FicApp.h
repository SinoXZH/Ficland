#ifndef __FICAPP_H__
#define __FICAPP_H__

#include "Archive.h"

class FicApp{
public: 
    FicApp();
    ~FicApp();

public:
    bool Init();
    bool Run();

protected:
    bool Design();
    bool CreateNewEmptyMatrixFile();
    bool LoadMatrixFile();
    bool SaveArchiveToXml();
    bool LoadXmlToArchive();
    bool InitWorld();

private:
    Archive curArchive;
};

#endif
