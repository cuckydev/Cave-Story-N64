#include "npcxxx.h"
#include "game.h"
#include "mychar.h"
#include "draw.h"
#include "sound.h"

//NPC 150 - Quote
#include "data/bitmap/mychar.inc.c"

void Npc150_Act(NPCHAR *npc)
{
	s32 i;
	
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			
			if (npc->direct > 10)
			{
				npc->x = gMC.x;
				npc->y = gMC.y;
				npc->direct -= 10;
			}
			break;
			
		case 2:
			npc->ani_no = 1;
			break;
			
		case 10:
			npc->act_no = 11;
			for (i = 0; i < 4; i++)
				SetNpChar(4, npc->x, npc->y, Random(-0x155, 0x155), Random(-0x600, 0), 0, NULL, 0x100);
			PlaySoundObject(71, 1);
			//Fallthrough
		case 11:
			npc->ani_no = 2;
			break;
			
		case 20:
			npc->act_no = 21;
			npc->act_wait = 64;
			PlaySoundObject(29, 1);
			//Fallthrough
		case 21:
			if (--npc->act_wait == 0)
				npc->cond = 0;
			break;
			
		case 50:
			npc->act_no = 51;
			npc->ani_no = 3;
			npc->ani_wait = 0;
			//Fallthrough
		case 51:
			if (++npc->ani_wait > 4)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			
			if (npc->ani_no > 6)
				npc->ani_no = 3;
			
			if (npc->direct == 0)
				npc->x -= 1 * 0x200;
			else
				npc->x += 1 * 0x200;
			break;
			
		case 60:
			npc->act_no = 61;
			npc->ani_no = 7;
			npc->tgt_x = npc->x;
			npc->tgt_y = npc->y;
			//Fallthrough
		case 61:
			npc->tgt_y += 0x100;
			npc->x = npc->tgt_x + (Random(-1, 1) * 0x200);
			npc->y = npc->tgt_y + (Random(-1, 1) * 0x200);
			break;
			
		case 70:
			npc->act_no = 71;
			npc->act_wait = 0;
			npc->ani_no = 3;
			npc->ani_wait = 0;
			//Fallthrough
		case 71:
			if (npc->direct == 0)
				npc->x += 0x100;
			else
				npc->x -= 0x100;
			
			if (++npc->ani_wait > 8)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 6)
				npc->ani_no = 3;
			break;

		case 80:
			npc->ani_no = 8;
			break;
			
		case 99:
		case 100:
			npc->act_no = 101;
			npc->ani_no = 3;
			npc->ani_wait = 0;
			//Fallthrough
		case 101:
			npc->ym += 0x40;
			if (npc->ym > 0x5FF)
				npc->ym = 0x5FF;
			
			if (npc->flag & 8)
			{
				npc->ym = 0;
				npc->act_no = 102;
			}
			
			npc->y += npc->ym;
			break;
			
		case 102:
			if (++npc->ani_wait > 8)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 6)
				npc->ani_no = 3;
			break;
	}
}

void Npc150_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{  0, 0,  16, 16},
		{ 48, 0,  64, 16},
		{144, 0, 160, 16},
		{ 16, 0,  32, 16},
		{  0, 0,  16, 16},
		{ 32, 0,  48, 16},
		{  0, 0,  16, 16},
		{160, 0, 176, 16},
		{112, 0, 128, 16},
	};
	RECT telerect;
	
	LoadTLUT_CI4(mychar_tlut);
	LoadTex_CI4(176, 16, mychar_tex + (88 * 16) * ((((gMC.equip & EQUIP_MIMIGA_MASK) != 0) * 2) + (npc->direct != 0)));
	
	if (npc->act_no == 21)
	{
		if (npc->act_wait / 2 % 2)
			telerect.left = rect[npc->ani_no].left + 1;
		else
			telerect.left = rect[npc->ani_no].left;
		telerect.right = rect[npc->ani_no].right;
		telerect.top = rect[npc->ani_no].top;
		telerect.bottom = telerect.top + (npc->act_wait / 4);
		
		PutBitmap(&telerect, x, y);
	}
	else
	{
		PutBitmap(&rect[npc->ani_no], x, y);
	}
}
