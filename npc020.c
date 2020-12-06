#include "npcxxx.h"
#include "game.h"
#include "caret.h"
#include "draw.h"

//NPC 021 - Open Chest
#include "data/bitmap/npc_chest.inc.c"

void Npc021_Act(NPCHAR *npc)
{
	if (npc->act_no == 0)
	{
		npc->act_no = 1;
		if (npc->direct == 2)
			npc->y += 16 * 0x200;
	}
}

void Npc021_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {48, 8, 64, 16};
	
	LoadTLUT_CI4(npc_chest_tlut);
	LoadTex_CI4(64, 16, npc_chest_tex);
	PutBitmap(&rect, x, y);
}

//NPC 030 - Gunsmith
#include "data/bitmap/npc_gunsmith.inc.c"

void Npc030_Act(NPCHAR *npc)
{
	//Do stuff
	if (npc->direct == 0)
	{
		switch (npc->act_no)
		{
			case 0:
				npc->act_no = 1;
				npc->ani_no = 0;
				npc->ani_wait = 0;
				//Fallthrough
			case 1:
				if (Random(0, 120) == 10)
				{
					npc->act_no = 2;
					npc->act_wait = 0;
					npc->ani_no = 1;
				}
				break;
				
			case 2:
				if (++npc->act_wait > 8)
				{
					npc->act_no = 1;
					npc->ani_no = 0;
				}
				break;
		}
	}
	else
	{
		if (npc->act_no == 0)
		{
			npc->act_no = 1;
			npc->y += 16 * 0x200;
			npc->ani_no = 2;
		}
		
		if (++npc->act_wait > 100)
		{
			npc->act_wait = 0;
			SetCaret(npc->x, npc->y - (2 * 0x200), 5, 0);
		}
	}
}

void Npc030_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
		{32, 0, 48, 16},
	};
	
	LoadTLUT_CI4(npc_gunsmith_tlut);
	LoadTex_CI4(48, 16, npc_gunsmith_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 032 - Life Capsule
#include "data/bitmap/npc_lifecapsule.inc.c"

void Npc032_Act(NPCHAR *npc)
{
	//Animate
	if (++npc->ani_wait > 2)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 1)
		npc->ani_no = 0;
}

void Npc032_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
	};
	
	LoadTLUT_CI4(npc_lifecapsule_tlut);
	LoadTex_CI4(32, 16, npc_lifecapsule_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}
