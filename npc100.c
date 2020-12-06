#include "npcxxx.h"
#include "game.h"
#include "draw.h"

//NPC 119 - Table and Chair
#include "data/bitmap/npc_tablechair.inc.c"

void Npc119_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 32, 16};
	
	LoadTLUT_CI4(npc_tablechair_tlut);
	LoadTex_CI4(32, 16, npc_tablechair_tex);
	PutBitmap(&rect, x, y);
}
