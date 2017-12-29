#ifndef __DEAL_SEED_H__
#define __DEAL_SEED_H__

#include "agent.h"

#define FULL_PROFILE     		"/data/assets/full_profile"
#define PROFILE_STORAGE_FILE	"/data/assets/fallback"
#define SORT_FALLBACK_FILE_NAME "/data/assets/sort_fallback"
#define CONFIG_FILE_NAME		"/data/assets/rt_config"

#define INT_SAVE_IN_FILE_LEN                     4
#define CONFIG_FILE_FALLBACK_LEN                 4
#define CONFIG_FILE_OFFSET_ICCID_LEN             22
#define CONFIG_FILE_OFFSET_PRIVIOUS_MCC_LEN      3
#define CID_LENGTH                               12
#define IMEI_LENGTH                              15
#define CONFIG_FILE_BUFFER_LENGTH                80
#define SORT_FALLBACK_NUM_HEAD_LEN               4
#define SORT_FALLBACK_BLOCK_SIZE                 50
#define REGISTER_DOC_INIT                        2
#define GROWTH_ROTE                              1.5//注网状态检测间隔倍率参数
#define ALL_NUM                                   "NUM:"
#define GET_MCC_CID_IMEI_FOR_AT

#define HEAD_LENGTH                                 2
#define LENGTH_BUFFER_SIZE                          4
#define DATA_FLAG_LENGTH                            4
#define MSG_OFFSET_ICCID_LEN                        22
#define ITEM_ICCID                                  0
#define ITEM_FALLBACK                               1
#define MAX_BLOCK_SIZE                              1024
#define PROFILE_IN_ASSETS							"/data/assets/profile"

#define   BLOCK_HEAD                                 "RT"
#define   BLOCK_DATA                                 "DATA"

bool init_seed(void);
int8_t  seed_create_fallback(int8_t *buf);
int8_t  seed_create_sort_fallback(int8_t *buf);
int8_t  seed_create_rt_config(void);
void    seed_exist(void);

#endif