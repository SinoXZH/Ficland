#ifndef __SOCIAL_STATUS__
#define __SOCIAL_STATUS__

#include "globals.h"


typedef enum {
    TITLE_NONE = 0,
    TITLE_BARON,
    TITLE_VISCOUNT,
    TITLE_COUNT,
    TITLE_MARQUIS,
    TITLE_DUKE,
    TITLE_KING,
    TITLE_EMPEROR,
    TITLE_CNT
}TITLE_ENUM;

const string titleString[TITLE_CNT] = 
{
    "",
    "�о�",
    "�Ӿ�",
    "����",
    "���",
    "����",
    "��",
    "�ʵ�"
};


typedef enum {
    JOB_NONE = 0,
    JOB_CITIZEN,
    JOB_MAID,
    JOB_CONCUBINE,
    JOB_ACADEMY_STUDENT,
    JOB_HOSPITAL_NURSE,
    JOB_ACADEMY_MAGIC_TEACHER,
    JOB_ACADEMY_FIGHTER_TEACHER,
    JOB_ACADEMY_ARCHER_TEACHER,
    JOB_HOSPITAL_DOCTOR,
    JOB_ACADEMY_PRESIDENT,
    JOB_HOSPITAL_PRESIDENT,
    JOB_LANDLORD,
    JOB_COUNT
}JOB_ENUM;

const string jobString[JOB_COUNT] =
{
    "",
    "����",
    "Ů��",
    "���",
    "ѧ��",
    "��ʿ",
    "ħ����ʦ",
    "������ʦ",
    "������ʦ",
    "ҽ��",
    "ѧԺԺ��",
    "ҽԺԺ��",
    "����"
};


class SocialStatus{
public:
    SocialStatus();
    ~SocialStatus();

public:
    void GenerateStatusScoreFromTitleAndJob();

    string GetTitleString();
    string GetJobString();

public:
    TITLE_ENUM nobleTitle;
    JOB_ENUM job;
    unsigned int statusScore;

    string manorName;
};


#endif //__SOCIAL_STATUS__