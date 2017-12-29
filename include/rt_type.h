#ifndef __RT_TYPE_H_
#define __RT_TYPE_H_

/**********************类型定义**************************/


/* There is some amount of overlap with <sys/types.h> as known by inet code */

typedef char     s8;
typedef short int       s16;
typedef int         	s32;
# if __WORDSIZE == 64
typedef long int        s64;
# else
__extension__
typedef long long int       s64;
# endif
#endif

/* Unsigned. */
typedef unsigned char       u8;
typedef unsigned short int u16;
#ifndef __uint32_t_defined
typedef unsigned int        u32;
# define __uint32_t_defined
#endif
#if __WORDSIZE == 64
typedef unsigned long int   u64;
#else
__extension__
typedef unsigned long long int u64;
/**********************类型定义**************************/


#endif