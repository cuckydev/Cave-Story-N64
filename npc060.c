#include "npcxxx.h"
#include "game.h"
#include "mychar.h"
#include "map.h"
#include "draw.h"
#include "sound.h"

//NPC 064 - First Cave Critter
#include "data/bitmap/npc_critter.inc.c"

void Npc064_Act(NPCHAR *npc)
{
	switch (npc->act_no)
	{
		case 0: //Initialize
			npc->y += 3 * 0x200;
			npc->act_no = 1;
			//Fallthrough
		case 1: //Waiting
			//Look at player
			if (npc->x > gMC.x)
				npc->direct = 0;
			else
				npc->direct = 2;
			
			if (npc->tgt_x < 100)
				npc->tgt_x++;
			
			//Open eyes near player
			if (npc->act_wait >= 8 && npc->x - (112 * 0x200) < gMC.x && npc->x + (112 * 0x200) > gMC.x && npc->y - (80 * 0x200) < gMC.y && npc->y + (80 * 0x200) > gMC.y)
			{
				npc->ani_no = 1;
			}
			else
			{
				if (npc->act_wait < 8)
					npc->act_wait++;
				npc->ani_no = 0;
			}
			
			//Jump if attacked
			if (npc->shock)
			{
				npc->act_no = 2;
				npc->ani_no = 0;
				npc->act_wait = 0;
			}
			
			//Jump if player is nearby
			if (npc->act_wait >= 8 && npc->tgt_x >= 100 && npc->x - (64 * 0x200) < gMC.x && npc->x + (64 * 0x200) > gMC.x && npc->y - (80 * 0x200) < gMC.y && npc->y + (48 * 0x200) > gMC.y)
			{
				npc->act_no = 2;
				npc->ani_no = 0;
				npc->act_wait = 0;
			}
			break;
			
		case 2: //Going to jump
			if (++npc->act_wait > 8)
			{
				//Set jump state
				npc->act_no = 3;
				npc->ani_no = 2;
				
				//Jump
				npc->ym = -0x5FF;
				PlaySoundObject(30, 1);
				
				//Jump in facing direction
				if (npc->direct == 0)
					npc->xm = -0x100;
				else
					npc->xm = 0x100;
			}
			break;
			
		case 3: //Jumping
			//Land
			if (npc->flag & 8)
			{
				npc->xm = 0;
				npc->act_wait = 0;
				npc->ani_no = 0;
				npc->act_no = 1;
				PlaySoundObject(23, 1);
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

void Npc064_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rcLeft[] = {
		{0, 0, 16, 16},
		{16, 0, 32, 16},
		{32, 0, 48, 16},
	};
	static const RECT rcRight[] = {
		{0, 16, 16, 32},
		{16, 16, 32, 32},
		{32, 16, 48, 32},
	};
	
	LoadTLUT_CI4(npc_critter_cemet_tlut);
	LoadTex_CI4(96, 32, npc_critter_tex);
	if (npc->direct)
		PutBitmap(&rcRight[npc->ani_no], x, y);
	else
		PutBitmap(&rcLeft[npc->ani_no], x, y);
}

//NPC 065 - First Cave Bat
#include "data/bitmap/npc_bat.inc.c"

void Npc065_Act(NPCHAR *npc)
{
	//Movement
	switch (npc->act_no)
	{
		case 0:
			npc->tgt_x = npc->x;
			npc->tgt_y = npc->y;
			npc->count1 = 120;
			npc->act_no = 1;
			npc->act_wait = Random(0, 50);
			//Fallthrough
		case 1:
			if (++npc->act_wait < 50)
				break;
			npc->act_wait = 0;
			npc->act_no = 2;
			npc->ym = 0x300;
			break;
			
		case 2:
			if (gMC.x < npc->x)
				npc->direct = 0;
			else
				npc->direct = 2;
			
			if (npc->tgt_y < npc->y)
				npc->ym -= 0x10;
			if (npc->tgt_y > npc->y)
				npc->ym += 0x10;
			
			if (npc->ym > 0x300)
				npc->ym = 0x300;
			if (npc->ym < -0x300)
				npc->ym = -0x300;
			break;
	}

	npc->x += npc->xm;
	npc->y += npc->ym;
	
	//Animate
	if (++npc->ani_wait > 1)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 2)
		npc->ani_no = 0;
}

void Npc065_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rcLeft[8] = {
		{ 32, 0,  48, 16},
		{ 48, 0,  64, 16},
		{ 64, 0,  80, 16},
		{ 80, 0,  96, 16},
	};
	static const RECT rcRight[8] = {
		{ 32, 16,  48, 32},
		{ 48, 16,  64, 32},
		{ 64, 16,  80, 32},
		{ 80, 16,  96, 32},
	};
	
	LoadTLUT_CI4(npc_bat_cemet_tlut);
	LoadTex_CI4(96, 32, npc_bat_tex);
	if (npc->direct)
		PutBitmap(&rcRight[npc->ani_no], x, y);
	else
		PutBitmap(&rcLeft[npc->ani_no], x, y);
}

//NPC 073 - Water Droplet
#include "data/bitmap/npc_waterdrop.inc.c"

void Npc073_Act(NPCHAR *npc)
{
	s16 map_l;
	
	//Select random frame
	npc->ani_no = Random(0, 4);
	
	//Fall and move
	npc->ym += 0x20;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	
	npc->x += npc->xm;
	npc->y += npc->ym;
	
	//Delete conditions
	if (++npc->act_wait > 10)
	{
		if (npc->flag & 1)
			npc->cond = 0;
		if (npc->flag & 4)
			npc->cond = 0;
		if (npc->flag & 8)
			npc->cond = 0;
		if (npc->flag & 0x100)
			npc->cond = 0;
	}
	
	GetMapData(NULL, NULL, &map_l);
	if (npc->y > map_l * 0x200 * 0x10)
		npc->cond = 0;
}

void Npc073_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rcLeft[] = {
		{0, 0,  2, 2},
		{2, 0,  4, 2},
		{4, 0,  6, 2},
		{6, 0,  8, 2},
		{8, 0, 10, 2},
	};
	static const RECT rcRight[] = {
		{0, 2,  2, 4},
		{2, 2,  4, 4},
		{4, 2,  6, 4},
		{6, 2,  8, 4},
		{8, 2, 10, 4},
	};
	
	LoadTLUT_CI4(npc_waterdrop_tlut);
	LoadTex_CI4(16, 4, npc_waterdrop_tex);
	if (npc->direct == 2)
		PutBitmap(&rcRight[npc->ani_no], x, y);
	else
		PutBitmap(&rcLeft[npc->ani_no], x, y);
}
