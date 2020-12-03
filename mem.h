#ifndef MEM_H
#define MEM_H

#include <ultra64.h>
#include <stddef.h>

u8 Mem_Init(void *ptr, size_t size);
void *Mem_Alloc(size_t size);
void Mem_Free(void *ptr);

#endif
