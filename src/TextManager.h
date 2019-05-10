#ifndef __TEXT_MANAGER_H__
#define __TEXT_MANAGER_H__


#include "globals.h"
#include "CharaDefine.h"
#include "Character.h"


class TextManager {
public:
    static TextManager* GetInstance();
    static void DelInstance();
    static void InitInstance(const string& path);

public:
    string GetRandomOrientalFamilyName();

    string GetRandomOrientalName(GENDER_ENUM gender);

    bool GetCharaIntroduction(Character* chara);

protected:
    TextManager(const string& path);
    ~TextManager();

    bool Init();

    vector<string> GetStringListFromFile(const string& filepath);

    string GetStringFromFile(const string& filepath);

    string GetFormatText(const string& format, ...);

protected:
    static TextManager* instance;
    string textPath;

    vector<string> orientalFamilyNameList;
    vector<string> orientalMaleNameList;
    vector<string> orientalFemaleNameList;
    set<string> existNameSet;

    string briefIntroduction;
};


#endif //__TEXT_MANAGER_H__
