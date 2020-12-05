#ifndef FLAGS_H
#define FLAGS_H

#include <ultra64.h>
#include "game_def.h"

//Flags globals
#define NPC_FLAG_BYTES 1000
#define SKIP_FLAG_BYTES 8

extern u8 gFlagNPC[NPC_FLAG_BYTES];
extern u8 gSkipFlag[SKIP_FLAG_BYTES];

//Flag functions
void InitFlags();
void InitSkipFlags();
void SetNPCFlag(s32 a);
void CutNPCFlag(s32 a);
BOOL GetNPCFlag(s32 a);
void SetSkipFlag(s32 a);
void CutSkipFlag(s32 a);
BOOL GetSkipFlag(s32 a);

#endif
