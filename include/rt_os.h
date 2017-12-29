#ifndef __RT_OS_H__
#define __RT_OS_H__

#include <memory.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <malloc.h>
#include <stdio.h>

#include "agent.h"

s32 rt_os_strcmp(void *mem_des,void *mem_src);
s32 rt_os_strncmp(void *mem_des,void *mem_src,s32 len);
s8 *rt_os_strcpy(char* dest, const char *src);
size_t rt_os_strlen(void *string);
s8 *rt_os_strchr(s8 *str, const s8 chr);
s8 *rt_os_strstr(s8 *str1, const s8 *str2);
s32 rt_os_access(const s8 *filenpath, s32 mode);

s32 rt_os_memcmp(void *mem_des,void *mem_src,s32 len);
void *rt_os_memset(void *mem,s8 value,s32 len);
void *rt_os_memcpy(void *mem_des,void *mem_src,s32 len);

void rt_os_free(void *mem);
void *rt_os_malloc(u32 size);

bool rt_send_queue_msg(s32 msgid,void *buffer,s32 len);
bool rt_receive_queue_msg(s32 msgid,void *buffer,s32 len);
s32 rt_creat_msg_queue(void);
bool rt_mutex_destroy(pthread_mutex_t *mutex);
bool rt_mutex_unlock(pthread_mutex_t *mutex);
bool rt_mutex_lock(pthread_mutex_t *mutex);
bool rt_mutex_init(pthread_mutex_t *mutex);
// bool rt_create_task(rt_task *task_id,rt_taskfun task_fun);
#endif /*The end*/
