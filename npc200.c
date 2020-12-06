#include "npcxxx.h"
#include "game.h"
#include "draw.h"

//NPC 211 - Spikes (small)
#include "data/bitmap/npc_spikes.inc.c"

void Npc211_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{  0, 0,  16, 16},
		{ 16, 0,  32, 16},
		{ 32, 0,  48, 16},
		{ 48, 0,  64, 16},
	};
	
	LoadTLUT_CI4(npc_spikes_tlut);
	LoadTex_CI4(64, 16, npc_spikes_tex);
	PutBitmap(&rect[npc->code_event], x, y);
}
