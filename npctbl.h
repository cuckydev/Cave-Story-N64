#ifndef NPCTBL_H
#define NPCTBL_H

#include "npchar.h"

typedef struct
{
	void (*act)(NPCHAR*);
	void (*put)(NPCHAR*, s32, s32);
} NPC_FUNC;

extern const NPC_FUNC gpNpcFuncTbl[];

#endif
