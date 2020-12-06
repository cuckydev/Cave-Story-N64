#include "npcxxx.h"
#include "game.h"
#include "mychar.h"
#include "draw.h"

//NPC 059 - Eye Door
#include "data/bitmap/npc_eyedoor.inc.c"

void Npc059_Act(NPCHAR *npc)
{
	//Movement and animation
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			// Fallthrough
		case 1:
			if (npc->x - (64 * 0x200) < gMC.x && npc->x + (64 * 0x200) > gMC.x && npc->y - (64 * 0x200) < gMC.y && npc->y + (64 * 0x200) > gMC.y)
			{
				npc->act_no = 2;
				npc->ani_wait = 0;
			}
			break;
			
		case 2:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no == 2)
				npc->act_no = 3;
			break;
			
		case 3:
			if (!(npc->x - (64 * 0x200) < gMC.x && npc->x + (64 * 0x200) > gMC.x && npc->y - (64 * 0x200) < gMC.y && npc->y + (64 * 0x200) > gMC.y))
			{
				npc->act_no = 4;
				npc->ani_wait = 0;
			}
			break;
			
		case 4:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				npc->ani_no--;
			}
			if (npc->ani_no == 0)
				npc->act_no = 1;
			break;
	}
}

void Npc059_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 24},
		{16, 0, 32, 24},
		{32, 0, 48, 24},
		{48, 0, 64, 24},
	};
	
	LoadTLUT_CI4(npc_eyedoor_tlut);
	LoadTex_CI4(64, 24, npc_eyedoor_tex);
	PutBitmap(&rect[(npc->shock != 0) ? 3 : npc->ani_no], x, y);
}
