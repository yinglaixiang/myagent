
/*******************************************************************************
 * Copyright (c) redtea mobile.
 * File name   : rt_mem.c
 * Date        : 2017.10.30
 * Note        :
 * Description :
 * Contributors: RT - create the file
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Sublime text 2
 *******************************************************************************/

#include "rt_os.h"

#if 1
#define rt_os_printf  TRACE_PRINT
#else
#define rt_os_printf(format,...)
#endif

#if 1
#define rt_os_error  TRACE_ERROR
#else
#define rt_os_error(format,...)
#endif

bool rt_create_task(rt_task *task_id,rt_taskfun task_fun)
{
    s32 ret = 0;
    ret = pthread_create(task_id,NULL,task_fun,NULL);
    if(ret != 0)
    {
        rt_os_error("create task error!!\n");
        return false;
    }
    return true;
}

//
bool rt_mutex_init(pthread_mutex_t *mutex)
{
    s32 ret = 0;
    ret = pthread_mutex_init(mutex, NULL);
    if(ret != 0)
    {
        rt_os_error("create mutex error!!\n");
        return false;
    }
    return true;
}

s32 rt_mutex_lock(pthread_mutex_t *mutex)
{
    s32 ret = 0;
    ret = pthread_mutex_lock(mutex);
    if(ret != 0)
    {
        rt_os_error("lock mutex error!!\n");
        return false;
    }
    return true;
}

bool rt_mutex_unlock(pthread_mutex_t *mutex)
{
    s32 ret = 0;
    ret = pthread_mutex_unlock(mutex);
    if(ret != 0)
    {
        rt_os_error("unlock mutex error!!\n");
        return false;
    }
    return true;
}

bool rt_mutex_destroy(pthread_mutex_t *mutex)
{
    s32 ret = 0;
    ret = pthread_mutex_destroy(mutex);
    if(ret != 0)
    {
        rt_os_error("destroy mutex error!!\n");
        return false;
    }
    return true;
}

//message queue
s32 rt_creat_msg_queue(void)
{
    s32 msgid = -1;
    key_t q_key;
    q_key = ftok(".",1);
    msgid = msgget(q_key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        rt_os_error("messge id \n");
    }
    return msgid;
}

bool rt_receive_queue_msg(s32 msgid,void *buffer,s32 len)
{
    if (msgrcv(msgid, buffer, len,0, 0) == -1)
    {
        rt_os_error("no message data\n");
        return false;
    }
    return true;
}

bool rt_send_queue_msg(s32 msgid,void *buffer,s32 len)
{
    if (msgsnd(msgid, buffer, len, 0) == -1)
    {
        rt_os_error("send message data error\n");
        return false;
    }
    return true;
}

//
void *rt_os_malloc(u32 size)
{
    return malloc(size);
}

void rt_os_free(void *mem)
{
    if(NULL==mem)
    {
        rt_os_error("memory is empty!\n");
        return;
    }
    free(mem);
}

void *rt_os_memset(void *mem,s8 value,s32 len)
{
    if(NULL==mem)
    {
        rt_os_error("memory is empty!\n");
        return NULL;
    }
    return memset(mem,value,len);
}

void *rt_os_memcmp(void *mem_des,void *mem_src,s32 len)
{
    if((NULL==mem_des)||(NULL==mem_src))
    {
        rt_os_error("memory is empty!\n");
        return false;
    }
    return memcmp(mem_des,mem_src,len);
}

size_t rt_os_strlen(void *string)
{
    if(NULL == string)
    {
        rt_os_error("memory is empty!\n");
        return 0;
    }
    return strlen(string);
}

s8 *rt_os_strcpy(char* dest, const char *src)
{
    if((NULL==dest)||(NULL==src))
    {
        rt_os_error("strcpy is empty!\n");
        return NULL;
    }
    return strcpy(dest,src);
}

s32 rt_os_strncmp(void *mem_des,void *mem_src,s32 len)
{
    if((NULL==mem_des)||(NULL==mem_src))
    {
        //rt_os_error("memory is empty!\n");
        return false;
    }
    return strncmp(mem_des,mem_src,len);
}

s32 rt_os_strcmp(void *mem_des,void *mem_src)
{
    if((NULL==mem_des)||(NULL==mem_src))
    {
        rt_os_error("memory is empty!\n");
        return false;
    }
    return strcmp(mem_des,mem_src);
}

void *rt_os_memcpy(void *mem_des,void *mem_src,s32 len)
{
    if((NULL==mem_des)||(NULL==mem_src))
    {
        rt_os_error("memory is empty!\n");
        return NULL;
    }
    if(len<=0)
    {
        return NULL;
    }
    return memcpy(mem_des,mem_src,len);
}

s32 rt_os_access(const s8 *filenpath, s32 mode)
{
    if(filenpath==NULL)
    {
        return false;
    }
    return access(filenpath,mode);
}

s8 *rt_os_strstr(s8 *str1, const s8 *str2)
{
    if((NULL==str1)||(NULL==str2))
    {
        rt_os_error("strstr is empty!\n");
        return NULL;
    }
    return strstr(str1,str2);
}

s8 *rt_os_strchr(s8 *str, const s8 chr)
{
    if(NULL==str)
    {
        rt_os_error("strstr is empty!\n");
        return NULL;
    }
    return strchr(str,chr);
}















