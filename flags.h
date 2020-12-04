#ifndef FLAGS_H
#define FLAGS_H

#include <ultra64.h>
#include "game_def.h"

//Flags constants
#define NPC_FLAG_BYTES 1000
#define SKIP_FLAG_BYTES 8

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
