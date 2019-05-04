#include "TextManager.h"


TextManager* TextManager::instance = NULL;

TextManager* TextManager::GetInstance()
{
    return instance;
}

void TextManager::DelInstance()
{
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

void TextManager::InitInstance(const string& path)
{
    if (instance == NULL) {
        instance = new TextManager(path);
        instance->Init();
    }
}

TextManager::TextManager(const string& path)
{
    textPath = path;
}

TextManager::~TextManager()
{

}

bool TextManager::Init()
{
    string filepath = textPath + PATH_SEPARATOR;
    filepath += "oriental_family_name.txt";
    orientalFamilyNameList = GetStringListFromFile(filepath);
    PrintInfo("Oriental family name count: %d", orientalFamilyNameList.size());

    filepath = textPath + PATH_SEPARATOR;
    filepath += "oriental_name_male.txt";
    orientalMaleNameList = GetStringListFromFile(filepath);
    PrintInfo("Oriental male name count: %d", orientalMaleNameList.size());

    filepath = textPath + PATH_SEPARATOR;
    filepath += "oriental_name_female.txt";
    orientalFemaleNameList = GetStringListFromFile(filepath);
    PrintInfo("Oriental female name count: %d", orientalFemaleNameList.size());

    return true;
}

vector<string> TextManager::GetStringListFromFile(const string& filepath)
{
    vector<string> ret;
    ifstream ifs;
    ifs.open(filepath, ios_base::in);
    if (!ifs.is_open()) {
        return ret;
    }

    while (!ifs.eof()) {
        string content;
        ifs >> content;
        ret.push_back(content);
    }

    ifs.close();

    return ret;
}

string TextManager::GetRandomOrientalFamilyName()
{
    if (orientalFamilyNameList.empty()) {
        return "";
    }

    unsigned int randNum = GetRandomNum(0, orientalFamilyNameList.size() - 1);
    return orientalFamilyNameList[randNum];
}

string TextManager::GetRandomOrientalName(GENDER_ENUM gender)
{
    string ret;

    if (orientalMaleNameList.empty() || orientalFemaleNameList.empty()) {
        return ret;
    }

    unsigned int trytimes = 0;
    
    while (trytimes < 10000) {
        if (gender == GENDER_MALE) {
            unsigned int firstNum = GetRandomNum(0, orientalMaleNameList.size() - 1);
            ret += orientalMaleNameList[firstNum];
            unsigned int oneOrTwo = GetRandomNum(0, 9);
            if (oneOrTwo < 7) {
                unsigned int secondNum = GetRandomNum(0, orientalMaleNameList.size() - 1);
                ret += orientalMaleNameList[secondNum];
            }
        } else if (gender == GENDER_FEMALE) {
            unsigned int firstNum = GetRandomNum(0, orientalFemaleNameList.size() - 1);
            ret += orientalFemaleNameList[firstNum];
            unsigned int oneOrTwo = GetRandomNum(0, 9);
            if (oneOrTwo < 7) {
                unsigned int secondNum = GetRandomNum(0, orientalMaleNameList.size() - 1);
                ret += orientalFemaleNameList[secondNum];
            }
        } else {
            break;
        }

        if (existNameSet.find(ret) == existNameSet.end()) {
            existNameSet.insert(ret);
            break;
        }

        ret.clear();
        ++trytimes;
    }

    return ret;
}

