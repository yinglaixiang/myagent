#ifndef RT_IO_H_
#define RT_IO_H_

#include <fstream>
#include "agent.h"


#define io_print TRACE_PRINT
#define io_error TRACE_ERROR




bool rt_io_read(const s8 *filename,u32 offset,s8 *buffer,u32 size);
bool rt_io_write(const s8 *filename,u32 offset,s8 *buffer,u32 size);
bool rt_io_create(const s8 *filename);
#endif