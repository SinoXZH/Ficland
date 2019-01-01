#ifndef __GLOBAL_DEFINE_H__
#define __GLOBAL_DEFINE_H__


typedef enum{
    LOG_INFO,
    LOG_ERROR
}ENUM_LOG_LEVEL;

const int RET_SUCCESS = 0;
const int RET_COMMON_ERR = -1;
const int RET_EXIT = 1;

const int MAX_STRING_LEN = 1024*1024;

#define SPLIT_LINE "*********************************************************************"

#define WELCOME "Welcome to Ficland!"

#define CHOOSE_OPTION "Please choose options below:"

#define INVALID_OPTION "Invalid option, please choose options below:"


#endif //__GLOBAL_DEFINE_H__