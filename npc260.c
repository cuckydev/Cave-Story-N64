#include "npcxxx.h"
#include "game.h"
#include "draw.h"

//NPC 278 - Littles
#include "data/bitmap/npc_littles.inc.c"

void Npc278_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			npc->xm = 0;
			//Fallthrough
		case 1:
			if (Random(0, 60) == 1)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 1;
			}
			
			if (Random(0, 60) == 1)
			{
				npc->act_no = 10;
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
			
		case 10:
			npc->act_no = 11;
			npc->act_wait = Random(0, 16);
			npc->ani_no = 0;
			npc->ani_wait = 0;
			
			if (Random(0, 9) % 2)
				npc->direct = 0;
			else
				npc->direct = 2;
			//Fallthrough
		case 11:
			if (npc->direct == 0 && npc->flag & 1)
				npc->direct = 2;
			else if (npc->direct == 2 && npc->flag & 4)
				npc->direct = 0;
			
			if (npc->direct == 0)
				npc->xm = -0x100;
			else
				npc->xm = 0x100;
			
			if (++npc->ani_wait > 4)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 1)
				npc->ani_no = 0;
			
			if (++npc->act_wait > 0x20)
				npc->act_no = 0;
			break;
	}
	
	//Fall and move
	npc->ym += 0x20;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc278_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rcPapa[2] = {
		{ 0, 0,  8, 8},
		{ 8, 0, 16, 8},
	};
	static const RECT rcMama[2] = {
		{16, 0, 24, 8},
		{24, 0, 32, 8},
	};
	static const RECT rcKodomo[2] = {
		{32, 0, 40, 8},
		{40, 0, 48, 8},
	};
	
	LoadTLUT_CI4(npc_littles_tlut);
	LoadTex_CI4(48, 8, npc_littles_tex);
	
	switch (npc->code_event)
	{
		case 200:
			PutBitmap(&rcPapa[npc->ani_no], x, y);
			break;
		case 210:
			PutBitmap(&rcPapa[npc->ani_no], x, y);
			break;
		default:
			PutBitmap(&rcKodomo[npc->ani_no], x, y);
			break;
	}
}
