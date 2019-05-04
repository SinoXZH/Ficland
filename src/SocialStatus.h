#ifndef __SOCIAL_STATUS__
#define __SOCIAL_STATUS__


typedef enum {
    TITLE_NONE = 0,
    TITLE_BARON,
    TITLE_VISCOUNT,
    TITLE_COUNT,
    TITLE_MARQUIS,
    TITLE_DUKE,
    TITLE_KING,
    TITLE_EMPEROR
}TITLE_ENUM;


typedef enum {
    JOB_NONE = 0,
    JOB_CITIZEN,
    JOB_MAID,
    JOB_CONCUBINE,
    JOB_ACADEMY_STUDENT,
    JOB_ACADEMY_TEACHER,
    JOB_ACADEMY_PRESIDENT,
    JOB_LANDLORD
}JOB_ENUM;


class SocialStatus{
public:
    SocialStatus();
    ~SocialStatus();

public:
    TITLE_ENUM nobleTitle;
    JOB_ENUM job;
};


#endif //__SOCIAL_STATUS__