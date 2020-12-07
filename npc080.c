#include "npcxxx.h"
#include "game.h"
#include "draw.h"
#include "back.h"

//NPC 087 - Heart
#include "data/bitmap/npc_heart.inc.c"

void Npc087_Act(NPCHAR *npc)
{
	//Animate
	if (npc->direct == 0)
	{
		if (++npc->ani_wait > 2)
		{
			npc->ani_wait = 0;
			npc->ani_no++;
		}
		if (npc->ani_no > 1)
			npc->ani_no = 0;
	}
	
	//Move
	if (gBack.type == 5 || gBack.type == 6)
	{
		if (npc->act_no == 0)
		{
			npc->act_no = 1;
			npc->ym = Random(-0x20, 0x20);
			npc->xm = Random(0x7F, 0x100);
		}
		
		npc->xm -= 8;
		
		if (npc->x < 80 * 0x200)
			npc->cond = 0;
		
		if (npc->x < -3 * 0x200)
			npc->x = -3 * 0x200;
		
		if (npc->flag & 1)
			npc->xm = 0x100;
		if (npc->flag & 2)
			npc->ym = 0x40;
		if (npc->flag & 8)
			npc->ym = -0x40;
		
		npc->x += npc->xm;
		npc->y += npc->ym;
	}
	
	//Delete after 550 frames
	if (npc->direct == 0)
		++npc->count1;
	if (npc->count1 > 550)
		npc->cond = 0;
}

void Npc087_Put(NPCHAR *npc, s32 x, s32 y)
{
	RECT rect2[2] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
	};
	
	RECT rect6[2] = {
		{32, 0, 48, 16},
		{48, 0, 64, 16},
	};
	
	RECT rcLast = {64, 0, 80, 16};
	
	if (npc->count1 > 547)
	{
		LoadTLUT_CI4(npc_heart_tlut);
		LoadTex_CI4(80, 16, npc_heart_tex);
		PutBitmap(&rcLast, x, y);
	}
	else if (!(npc->count1 > 500 && npc->count1 / 2 % 2))
	{
		LoadTLUT_CI4(npc_heart_tlut);
		LoadTex_CI4(80, 16, npc_heart_tex);
		switch (npc->exp)
		{
			case 2:
				PutBitmap(&rect2[npc->ani_no], x, y);
				break;
			case 6:
				PutBitmap(&rect6[npc->ani_no], x, y);
				break;
		}
	}
}
