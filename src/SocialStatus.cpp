#include "SocialStatus.h"

SocialStatus::SocialStatus()
    : statusScore(0)
{

}

SocialStatus::~SocialStatus()
{
    
}

void SocialStatus::GenerateStatusScoreFromTitleAndJob()
{
    statusScore = 10 * (unsigned int)nobleTitle;
    if (job == JOB_ACADEMY_PRESIDENT
        || job == JOB_HOSPITAL_PRESIDENT) {
        statusScore += 20;
    }
    else if (job == JOB_ACADEMY_ARCHER_TEACHER
        || job == JOB_ACADEMY_FIGHTER_TEACHER
        || job == JOB_ACADEMY_MAGIC_TEACHER
        || job == JOB_HOSPITAL_DOCTOR) {
        statusScore += 10;
    }
}

string SocialStatus::GetTitleString()
{
    return titleString[nobleTitle];
}

string SocialStatus::GetJobString()
{
    return jobString[job];
}


