#ifndef MEM_H
#define MEM_H

#include <ultra64.h>
//typedef unsigned long long size_t;

u8 Mem_Init(void *ptr, size_t size);
void *Mem_Alloc(size_t size);
void Mem_Free(void *ptr);
void Mem_GetStat(size_t *used, size_t *size, size_t *max);

#endif
