#include "npcxxx.h"
#include "game.h"
#include "caret.h"
#include "draw.h"

//NPC 300 - Demon Crown
#include "data/bitmap/npc_demoncrown.inc.c"

void Npc300_Act(NPCHAR *npc)
{
	if (npc->act_no == 0)
	{
		npc->act_no = 1;
		npc->y += 6 * 0x200;
	}
	
	if (++npc->ani_wait % 8 == 1)
		SetCaret(npc->x + (Random(-8, 8) * 0x200), npc->y + (8 * 0x200), 13, 1);
}

void Npc300_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 16, 16};
	LoadTLUT_CI4(npc_demoncrown_tlut);
	LoadTex_CI4(16, 16, npc_demoncrown_tex);
	PutBitmap(&rect, x, y);
}
