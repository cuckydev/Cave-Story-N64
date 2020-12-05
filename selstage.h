#ifndef SELSTAGE_H
#define SELSTAGE_H

#include <ultra64.h>
#include "game_def.h"

//Permit stage structure
typedef struct
{
	s32 index;
	s32 event;
} PERMIT_STAGE;

#define PERMIT_STAGE_MAX 8

extern PERMIT_STAGE gPermitStage[PERMIT_STAGE_MAX];

//Stage select functions
void ClearPermitStage();
BOOL AddPermitStage(s32 index, s32 event);
BOOL SubPermitStage(s32 index);

#endif
