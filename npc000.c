#include "npcxxx.h"
#include "game.h"
#include "triangle.h"
#include "draw.h"

//NPC 000 - Null
void Npc000_Act(NPCHAR *npc)
{
	if (npc->act_no == 0)
	{
		npc->act_no = 1;
		if (npc->direct == 2)
			npc->y += 16 * 0x200;
	}
}

//NPC 004 - Smoke
#include "data/bitmap/npc_smoke.inc.c"

void Npc004_Act(NPCHAR *npc)
{
	u8 deg;
	
	if (npc->act_no == 0)
	{
		//Move in random direction at random speed
		if (npc->direct == 0 || npc->direct == 1)
		{
			deg = Random(0, 0xFF);
			npc->xm = GetCos(deg) * Random(0x200, 0x5FF) / 0x200;
			npc->ym = GetSin(deg) * Random(0x200, 0x5FF) / 0x200;
		}
		
		//Set state
		npc->ani_no = Random(0, 4);
		npc->ani_wait = Random(0, 3);
		npc->act_no = 1;
	}
	else
	{
		//Slight drag
		npc->xm = (npc->xm * 20) / 21;
		npc->ym = (npc->ym * 20) / 21;
		
		//Move
		npc->x += npc->xm;
		npc->y += npc->ym;
	}
	
	//Animate
	if (++npc->ani_wait > 4)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 7)
		npc->cond = 0;
}

void Npc004_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rcLeft[8] = {
		{  0, 0,  16, 16},
		{ 16, 0,  32, 16},
		{ 32, 0,  48, 16},
		{ 48, 0,  64, 16},
		{ 64, 0,  80, 16},
		{ 80, 0,  96, 16},
		{ 96, 0, 112, 16},
		{112, 0, 128, 16},
	};
	static const RECT rcUp[8] = {
		{  0, 16,  16, 32},
		{ 16, 16,  32, 32},
		{ 32, 16,  48, 32},
		{ 48, 16,  64, 32},
		{ 64, 16,  80, 32},
		{ 80, 16,  96, 32},
		{ 96, 16, 112, 32},
		{112, 16, 128, 32},
	};
	
	LoadTLUT_CI4(npc_smoke_tlut);
	LoadTex_CI4(128, 32, npc_smoke_tex);
	if (npc->direct == 1)
		PutBitmap(&rcUp[npc->ani_no], x, y);
	else
		PutBitmap(&rcLeft[npc->ani_no], x, y);
}

//NPC 015 - Closed Chest
#include "data/bitmap/npc_chest.inc.c"

void Npc015_Act(NPCHAR *npc)
{
	s32 i;
	
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->bits |= NPC_INTERACTABLE;
			
			if (npc->direct == 2)
			{
				npc->ym = -0x200;
				for (i = 0; i < 4; ++i)
					SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			}
			//Fallthrough
		case 1:
			npc->ani_no = 0;
			if (Random(0, 30) == 0)
				npc->act_no = 2;
			break;
			
		case 2:
			if (++npc->ani_wait > 1)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 2)
			{
				npc->ani_no = 0;
				npc->act_no = 1;
			}
			break;
	}
	
	//Fall and move
	npc->ym += 0x40;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	npc->y += npc->ym;
}

void Npc015_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[8] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
		{32, 0, 48, 16},
	};
	
	LoadTLUT_CI4(npc_chest_tlut);
	LoadTex_CI4(64, 16, npc_chest_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 016 - Save Point
#include "data/bitmap/npc_save.inc.c"

void Npc016_Act(NPCHAR *npc)
{
	s32 i;
	
	//Update
	switch (npc->act_no)
	{
		case 0:
			npc->bits |= NPC_INTERACTABLE;
			npc->act_no = 1;
			
			if (npc->direct == 2)
			{
				npc->bits &= ~NPC_INTERACTABLE;
				npc->ym = -0x200;
				for (i = 0; i < 4; ++i)
					SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			}
			
			//Fallthrough
		case 1:
			if (npc->flag & 8)
				npc->bits |= NPC_INTERACTABLE;
			break;
	}
	
	//Animate
	if (++npc->ani_wait > 2)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 7)
		npc->ani_no = 0;
	
	//Fall
	npc->ym += 0x40;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	npc->y += npc->ym;
}

void Npc016_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[8] = {
		{  0, 0,  16, 16},
		{ 16, 0,  32, 16},
		{ 32, 0,  48, 16},
		{ 48, 0,  64, 16},
		{ 64, 0,  80, 16},
		{ 80, 0,  96, 16},
		{ 96, 0, 112, 16},
		{112, 0, 128, 16},
	};
	
	LoadTLUT_CI4(npc_save_tlut);
	LoadTex_CI4(128, 16, npc_save_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 017 - Health Refill
#include "data/bitmap/npc_healthrefill.inc.c"

void Npc017_Act(NPCHAR *npc)
{
	s32 a;
	
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			
			if (npc->direct == 2)
			{
				npc->ym = -0x200;
				for (a = 0; a < 4; ++a)
					SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			}
			
			//Fallthrough
		case 1:
			a = Random(0, 30);
			
			if (a < 10)
				npc->act_no = 2;
			else if (a < 25)
				npc->act_no = 3;
			else
				npc->act_no = 4;
			
			npc->act_wait = Random(0x10, 0x40);
			npc->ani_wait = 0;
			break;
			
		case 2:
			npc->ani_no = 0;
			if (--npc->act_wait == 0)
				npc->act_no = 1;
			break;
			
		case 3:
			npc->ani_no = !(++npc->ani_wait % 2);
			if (--npc->act_wait == 0)
				npc->act_no = 1;
			break;
			
		case 4:
			npc->ani_no = 1;
			if (--npc->act_wait == 0)
				npc->act_no = 1;
			break;
	}
	
	//Fall
	npc->ym += 0x40;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	npc->y += npc->ym;
}

void Npc017_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{  0, 0,  16, 16},
		{ 16, 0,  32, 16},
	};
	
	LoadTLUT_CI4(npc_healthrefill_tlut);
	LoadTex_CI4(32, 16, npc_healthrefill_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 018 - Door
#include "data/bitmap/npc_door.inc.c"

void Npc018_Act(NPCHAR *npc)
{
	s32 i;
	switch (npc->act_no)
	{
		case 0:
			if (npc->direct == 0)
				npc->ani_no = 0;
			else
				npc->ani_no = 1;
			break;
			
		case 1:
			for (i = 0; i < 4; ++i)
				SetNpChar(4, npc->x, npc->y, Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			npc->act_no = 0;
			npc->ani_no = 0;
			break;
	}
}

void Npc018_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2] = {
		{  0, 0,  16, 24},
		{ 16, 0,  32, 24},
	};
	
	LoadTLUT_CI4(npc_door_tlut);
	LoadTex_CI4(32, 24, npc_door_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}
