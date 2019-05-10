#ifndef __CHARADEFINE_H__
#define __CHARADEFINE_H__

typedef enum {
    RACE_UNKNOWN = -1,
    RACE_HUMAN_SINIAN = 0,
    RACE_HUMAN_JAPIAN,
    RACE_HUMAN_NORDIAN,
    RACE_HUMAN_TICIAN,
    RACE_HUMAN_ROSSIAN,
    RACE_HUMAN_TARTAIN,
    RACE_ELF_LIGHT,
    RACE_ELF_DARK,
    RACE_DEOR_DEVERN,
    RACE_DEOR_DEVIA,
    RACE_COUNT
}RACE_ENUM;

typedef enum {
    GENDER_UNKNOWN = -1,
    GENDER_MALE = 0,
    GENDER_FEMALE
}GENDER_ENUM;

const unsigned int LANDLORD_EVERAGE_AGE = 40;
const unsigned int PRESIDENT_EVERAGE_AGE = 40;
const unsigned int DOCTOR_EVERAGE_AGE = 35;
const unsigned int NURSE_EVERAGE_AGE = 22;
const unsigned int TEACHER_EVERAGE_AGE = 32;
const unsigned int CONCUBINE_EVERAGE_AGE = 28;
const unsigned int STUDENT_EVERAGE_AGE = 18;


#endif //__CHARADEFINE_H__
