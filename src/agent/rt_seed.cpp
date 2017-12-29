#include "rt_seed.h"

#if 1
#define seed_printf  TRACE_PRINT
#else
#define seed_printf(format,...)
#endif

#if 1
#define seed_error  TRACE_ERROR
#else
#define seed_error(format,...)
#endif

/*******************************************************************************
 * Copyright (c) alai
 * File name   : If_File_Exit
 * Date        : 2017.09.019
 * Note        :
 * Description :
 To determine whether a file exists
 *******************************************************************************/
int32_t seed_access(int8_t *filename)
{
    int32_t ret = 0;
    ret = rt_os_access(filename,F_OK);
    return ret;
}

/*******************************************************************************
 * Copyright (c) alai
 * File name   : get_full_profile_info
 * Date        : 2017.09.019
 * Note        :
 * Description :
 * Test configuration file exists
 *******************************************************************************/
void seed_exist(void)
{
    struct stat statbuf;
    int8_t *buffer=NULL;
    uint32_t file_len = 0;

    do{
        if(seed_access(PROFILE_STORAGE_FILE)==-1)
        {
            seed_printf("fallback file not exit \n");
        }

        else if(seed_access(SORT_FALLBACK_FILE_NAME)==-1)
        {
            seed_printf("sort_fallback file not exit \n");
        }

        else if(seed_access(CONFIG_FILE_NAME)==-1)
        {
            seed_printf("rt_config file not exit \n");
        }
        else
        {
            break;
        }

        stat(FULL_PROFILE,&statbuf);
        file_len=statbuf.st_size;

        if((buffer = (int8_t *)rt_os_malloc(file_len+1)) == NULL)
        {
            seed_error("malloc error \n");
            break;
        }
        if(rt_io_read(FULL_PROFILE,0,buffer,file_len) == false)
        {
            seed_error("read buffer error \n");
            break;
        }
        buffer[file_len]='\0';
        if(seed_create_fallback(buffer)<0)
        {
            seed_error("create fallback \n");
        }
        if(seed_create_sort_fallback(buffer)<0)
        {
            seed_error("create sort fallback error \n");
        }
        if(seed_create_rt_config(buffer)<0)
        {
            seed_error("create rt config \n");
        }
        break;
    }while(1);
    rt_os_free(buffer);
}

/*******************************************************************************
 * Copyright (c) alai
 * File name   : falllback_create_rt_config_file
 * Date        : 2017.09.019
 * Note        :
 * Description :
 * create re_config file
 *******************************************************************************/
bool seed_create_rt_config(void)
{
    int8_t ret = false;
    int32_t fd;

    do{
        if(rt_io_create(CONFIG_FILE_NAME) == false)
        {
            seed_error("open create rt_config error\n");
            break;
        }
        ret = true;
        break;
    }while(1);
    return ret;
}

/*******************************************************************************
 * Copyright (c) alai
 * File name   : get_full_profile_info
 * Date        : 2017.09.19
 * Note        :
 * Description :
 * create sort_fallnack file
 *******************************************************************************/
bool seed_create_sort_fallback(int8_t *buf)
{
    int8_t ret = false;
    int8_t *fill = NULL;
    int8_t *info = NULL;
    cJSON *agent_msg = NULL;
    cJSON *profile_info = NULL;
    cJSON *iccid = NULL;
    cJSON *fallback = NULL;
    cJSON *sort_fallback = NULL;
    int32_t size = 0;

    size = SORT_FALLBACK_NUM_HEAD_LEN+SORT_FALLBACK_BLOCK_SIZE+INT_SAVE_IN_FILE_LEN;
    do{
        if((agent_msg=cJSON_Parse(buf))==NULL)
        {
            seed_error("cJSON_Parse error \n");
            break;
        }
        profile_info=cJSON_GetObjectItem(agent_msg,"profileInfo");
        if(profile_info==NULL)
        {
            seed_error("cJSON_Parse error \n");
            break;
        }
        iccid=cJSON_GetObjectItem(profile_info,"iccid");
        if(iccid==NULL)
        {
            seed_error("cJSON_Parse error \n");
            break;
        }
        fallback=cJSON_GetObjectItem(profile_info,"fallback");
        if(fallback==NULL)
        {
            seed_error("cJSON_Parse error \n");
            break;
        }

        seed_printf(" iccid : %s,fallback %d\n ",\
            iccid->valuestring,fallback->valueint);
        if((sort_fallback=cJSON_CreateObject())==NULL)
        {
            seed_error("sort_fallback create error \n");
            break;
        }
        cJSON_AddItemToObject(sort_fallback,"iccid",cJSON_CreateString(iccid->valuestring));
        cJSON_AddItemToObject(sort_fallback,"fallback",cJSON_CreateNumber(fallback->valueint));
        info=cJSON_PrintUnformatted(sort_fallback);
        if((fill=rt_os_malloc(size))==NULL)
        {
            seed_error("malloc error \n");
            break;
        }
        rt_os_memset(fill,'F',size);

        sprintf(fill,"%s%4d%s",ALL_NUM,0,info);

        if(rt_io_create(SORT_FALLBACK_FILE_NAME) == false)
        {
            seed_error("write error \n");
            break;
        }

        if(rt_io_write(SORT_FALLBACK_FILE_NAME,0,fill,size) == false)
        {
            seed_error(" rt_write_data error \n");
            break;
        }
        ret = true;
        break;
    }while(1);

    if(sort_fallback!=NULL)
    {
        cJSON_Delete(sort_fallback);
    }

    rt_os_free(fill);
    if(agent_msg!=NULL)
    {
        cJSON_Delete(agent_msg);
    }
    return ret;
}

/*******************************************************************************
 * Copyright (c) alai
 * File name   : get_full_profile_info
 * Date        : 2017.09.019
 * Note        :
 * Description :
 * create fallback file
 *******************************************************************************/
bool seed_create_fallback(int8_t *buf)
{
    int8_t ret = false;
    int8_t *fill=NULL;
    int8_t *ptr=NULL;
    cJSON *agent_msg=NULL;
    cJSON *profile=NULL;

    do
    {
        if((agent_msg=cJSON_Parse(buf))==NULL)
        {
            seed_error("cJSON_Parse error \n");
            break;
        }
        //delete profile item
        profile=cJSON_DetachItemFromObject(agent_msg,"profile");

        if(seed_access(PROFILE_IN_ASSETS) == -1)
        {
            if(rt_io_create(PROFILE_IN_ASSETS) == false)
            {
                seed_error("create error \n");
                break;
            }
            vsim_insert_profile(profile->valuestring,strlen(profile->valuestring));
        }

        if(profile == NULL)
        {
            seed_error("cJSON_Parse error \n");
            break;
        }
        cJSON_AddItemToObject(agent_msg,"profile_id",cJSON_CreateNumber(0));

        if((fill=rt_os_malloc(MAX_BLOCK_SIZE))==NULL)
        {
            seed_error("malloc error \n");
            break;
        }
        rt_os_memset(fill,'F',MAX_BLOCK_SIZE);
        ptr=cJSON_Print(agent_msg);
        sprintf(fill,"%s%4d%s%s",BLOCK_HEAD,strlen(ptr),BLOCK_DATA,ptr);
        if(rt_io_create(PROFILE_STORAGE_FILE) == false)
        {
            seed_error("create error \n");
            break;
        }

        if(rt_io_write(PROFILE_STORAGE_FILE,0,fill,MAX_BLOCK_SIZE) == false)
        {
            seed_error(" rt_write_data error \n");
            break;
        }

        ret = true;
        break;
    }while(1);

    rt_os_free(fill);
    if(agent_msg!=NULL)
    {
        cJSON_Delete(agent_msg);
    }
    return ret;
}

bool init_seed(void)
{
   seed_exist();
   return true;
}
