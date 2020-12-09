#ifndef BOSSLIFE_H
#define BOSSLIFE_H

#include <ultra64.h>
#include "game_def.h"

//Boss life structure
typedef struct
{
	BOOL flag;
	s32 id;
	s32 *pId;
	s32 *pLife;
	s32 max;
	s32 br;
	s32 count;
} BOSSLIFE;

extern BOSSLIFE gBL;

//Boss life functions
void InitBossLife();
BOOL StartBossLife(s32 code_event);
BOOL StartBossLife2();
void PutBossLife();

#endif
