#ifndef DEBUG_H_
#define DEBUG_H_

#include "agent.h"

#if DEBUG

#define TRACE_PRINT(format,...) \
    do{\
        printf("RT_INFO[<%s>-(%d)] ",__FUNCTION__ , __LINE__); \
        printf(format,##__VA_ARGS__); \
    }while(0);
#define TRACE_ERROR(format,...) \
    do{\
        printf("RT_ERROR[<%s>-(%d):]",__FUNCTION__ , __LINE__); \
        printf(format,##__VA_ARGS__); \
    }while(0);

#else

#define TRACE_PRINT(format,...)
#define TRACE_ERROR(format,...)

#endif






#endif