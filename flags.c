#include "flags.h"
#include <string.h>

//Macros for setting, un-setting and getting flags
//Each flag is stored in a bit, so we can use the exact same macros we'd use for bits
#define SET_FLAG(x, i) ((x)[(i) / 8] |= 1 << ((i) % 8))
#define UNSET_FLAG(x, i) ((x)[(i) / 8] &= ~(1 << ((i) % 8)))
#define GET_FLAG(x, i) ((x)[(i) / 8] & (1 << ((i) % 8)))

//Flags
u8 gFlagNPC[NPC_FLAG_BYTES];
u8 gSkipFlag[SKIP_FLAG_BYTES];

//Flag initializers
void InitFlags()
{
	memset(gFlagNPC, 0, sizeof(gFlagNPC));
}

void InitSkipFlags()
{
	memset(gSkipFlag, 0, sizeof(gSkipFlag));
}

//NPC flags
void SetNPCFlag(s32 a)
{
	if (a < 0 || a >= (NPC_FLAG_BYTES * 8))
		return;
	SET_FLAG(gFlagNPC, a);
}

void CutNPCFlag(s32 a)
{
	if (a < 0 || a >= (NPC_FLAG_BYTES * 8))
		return;
	UNSET_FLAG(gFlagNPC, a);
}

BOOL GetNPCFlag(s32 a)
{
	if (a < 0 || a >= (NPC_FLAG_BYTES * 8))
		return FALSE;
	if (GET_FLAG(gFlagNPC, a))
		return TRUE;
	else
		return FALSE;
}

//Skip flags
void SetSkipFlag(s32 a)
{
	if (a < 0 || a >= (SKIP_FLAG_BYTES * 8))
		return;
	SET_FLAG(gSkipFlag, a);
}

void CutSkipFlag(s32 a)
{
	if (a < 0 || a >= (SKIP_FLAG_BYTES * 8))
		return;
	UNSET_FLAG(gSkipFlag, a);
}

BOOL GetSkipFlag(s32 a)
{
	if (a < 0 || a >= (SKIP_FLAG_BYTES * 8))
		return FALSE;
	if (GET_FLAG(gSkipFlag, a))
		return TRUE;
	else
		return FALSE;
}
