#include "npcxxx.h"
#include "game.h"
#include "draw.h"
#include "mychar.h"
#include "back.h"
#include "sound.h"

//NPC 080 - Gravekeeper
#include "data/bitmap/npc_gravekeeper.inc.c"

void Npc080_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->bits &= ~NPC_SHOOTABLE;
			npc->act_no = 1;
			npc->damage = 0;
			npc->hit.front = 4 * 0x200;
			//Fallthrough
		case 1:
			npc->ani_no = 0;
			
			if (npc->x - (128 * 0x200) < gMC.x && npc->x + (128 * 0x200) > gMC.x && npc->y - (48 * 0x200) < gMC.y && npc->y + (32 * 0x200) > gMC.y)
			{
				npc->ani_wait = 0;
				npc->act_no = 2;
			}
			
			if (npc->shock)
			{
				npc->ani_no = 1;
				npc->ani_wait = 0;
				npc->act_no = 2;
				npc->bits &= ~NPC_SHOOTABLE;
			}
			
			if (gMC.x < npc->x)
				npc->direct = 0;
			else
				npc->direct = 2;
			break;
			
		case 2:
			if (++npc->ani_wait > 6)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 3)
				npc->ani_no = 0;
			
			if (npc->x - (16 * 0x200) < gMC.x && npc->x + (16 * 0x200) > gMC.x)
			{
				npc->hit.front = (18 * 0x200);
				npc->act_wait = 0;
				npc->act_no = 3;
				npc->bits |= NPC_SHOOTABLE;
				PlaySoundObject(34, 1);
				
				if (npc->direct == 0)
					npc->xm = -0x400;
				else
					npc->xm = 0x400;
			}
			
			if (gMC.x < npc->x)
			{
				npc->direct = 0;
				npc->xm = -0x100;
			}
			else
			{
				npc->direct = 2;
				npc->xm = 0x100;
			}
			break;
			
		case 3:
			npc->xm = 0;
			
			if (++npc->act_wait > 40)
			{
				npc->act_wait = 0;
				npc->act_no = 4;
				PlaySoundObject(106, 1);
			}
			
			npc->ani_no = 4;
			break;
			
		case 4:
			npc->damage = 10;
			
			if (++npc->act_wait > 2)
			{
				npc->act_wait = 0;
				npc->act_no = 5;
			}
			npc->ani_no = 5;
			break;
			
		case 5:
			npc->ani_no = 6;
			if (++npc->act_wait > 60)
				npc->act_no = 0;
			break;
	}
	
	//Stop when hitting a wall
	if (npc->xm < 0 && npc->flag & 1)
		npc->xm = 0;
	if (npc->xm > 0 && npc->flag & 4)
		npc->xm = 0;
	
	//Fall and move
	npc->ym += 0x20;
	if (npc->xm > 0x400)
		npc->xm = 0x400;
	if (npc->xm < -0x400)
		npc->xm = -0x400;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	if (npc->ym < -0x5FF)
		npc->ym = -0x5FF;
	
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc080_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{  0, 0,  24, 24},
		{ 24, 0,  48, 24},
		{  0, 0,  24, 24},
		{ 48, 0,  72, 24},
		{ 72, 0,  96, 24},
		{ 96, 0, 120, 24},
		{120, 0, 144, 24},
	};
	
	LoadTLUT_CI4(npc_gravekeeper_tlut);
	LoadTex_CI4(144, 24, npc_gravekeeper_tex + (72 * 24) * (npc->direct != 0));
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 081 - Big Pignon
#include "data/bitmap/npc_bigpignon.inc.c"

void Npc081_Act(NPCHAR *npc)
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
			if (Random(0, 100) == 1)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 1;
				break;
			}
			
			if (Random(0, 150) == 1)
			{
				if (npc->direct == 0)
					npc->direct = 2;
				else
					npc->direct = 0;
			}
			
			if (Random(0, 150) == 1)
			{
				npc->act_no = 3;
				npc->act_wait = 50;
				npc->ani_no = 0;
				break;
			}
			break;
			
		case 2:
			if (++npc->act_wait > 8)
			{
				npc->act_no = 1;
				npc->ani_no = 0;
			}
			break;
			
		case 3:
			npc->act_no = 4;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			//Fallthrough
		case 4:
			if (--npc->act_wait == 0)
				npc->act_no = 0;
			
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 4)
				npc->ani_no = 2;
			
			if (npc->flag & 1)
			{
				npc->direct = 2;
				npc->xm = 0x200;
			}
			if (npc->flag & 4)
			{
				npc->direct = 0;
				npc->xm = -0x200;
			}
			
			if (npc->direct == 0)
				npc->xm = -0x100;
			else
				npc->xm = 0x100;
			break;
			
		case 5:
			if (npc->flag & 8)
				npc->act_no = 0;
			break;
	}
	
	switch (npc->act_no)
	{
		case 1:
		case 2:
		case 4:
			if (npc->shock)
			{
				npc->ym = -0x200;
				npc->ani_no = 5;
				npc->act_no = 5;
				
				if (npc->x < gMC.x)
					npc->xm = 0x100;
				else
					npc->xm = -0x100;
			}
			break;
	}
	
	//Fall and move
	npc->ym += 0x40;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc081_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0,  24, 24},
		{24, 0,  48, 24},
		{48, 0,  72, 24},
		{72, 0,  96, 24},
		{ 0, 0,  24, 24},
		{96, 0, 120, 24},
	};
	
	LoadTLUT_CI4(npc_bigpignon_tlut);
	LoadTex_CI4(128, 24, npc_bigpignon_tex + (64 * 24) * (npc->direct != 0));
	PutBitmap(&rect[npc->ani_no], x, y);
}

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

//NPC 091 - Cage
#include "data/bitmap/npc_cage.inc.c"

void Npc091_Act(NPCHAR *npc)
{
	if (npc->act_no == 0)
	{
		npc->act_no++;
		npc->y += 16 * 0x200;
	}
}

void Npc091_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 32, 24};
	LoadTLUT_CI4(npc_cage_tlut);
	LoadTex_CI4(48, 32, npc_cage_tex);
	PutBitmap(&rect, x, y);
}
