#include "npchar.h"
#include <string.h>

#include "data/npc_tbl.inc.c"

//NPC globals
NPCHAR gNPC[NPC_MAX];
s32 gCurlyShoot_wait;
s32 gCurlyShoot_x;
s32 gCurlyShoot_y;
s32 gSuperXpos;
s32 gSuperYpos;

//NPC functions
void InitNpChar()
{
	memset(gNPC, 0, sizeof(gNPC));
}
