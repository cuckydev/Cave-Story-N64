#include "npcxxx.h"
#include "game.h"
#include "triangle.h"
#include "draw.h"
#include "sound.h"
#include "mychar.h"
#include "frame.h"
#include "map.h"
#include "back.h"

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

//NPC 001 - Experience
#include "data/bitmap/npc_exp.inc.c"

void Npc001_Act(NPCHAR *npc)
{
	if (gBack.type == 5 || gBack.type == 6)
	{
		if (npc->act_no == 0)
		{
			//Set state
			npc->act_no = 1;
			
			//Set random speed
			npc->ym = Random(-0x80, 0x80);
			npc->xm = Random(0x7F, 0x100);
		}
		
		//Blow to the left
		npc->xm -= 8;
		
		//Destroy when off-screen
		if (npc->x < 80 * 0x200)
			npc->cond = 0;
		
		//Limit speed
		if (npc->xm < -0x600)
			npc->xm = -0x600;
		
		//Bounce off walls
		if (npc->flag & 1)
			npc->xm = 0x100;
		if (npc->flag & 2)
			npc->ym = 0x40;
		if (npc->flag & 8)
			npc->ym = -0x40;
	}
	else
	{
		if (npc->act_no == 0)
		{
			//Set state
			npc->act_no = 1;
			npc->ani_no = Random(0, 4);
			
			//Random speed
			npc->xm = Random(-0x200, 0x200);
			npc->ym = Random(-0x400, 0);
			
			//Random direction (reverse animation or not)
			if (Random(0, 1) != 0)
				npc->direct = 0;
			else
				npc->direct = 2;
		}
		
		//Gravity
		if (npc->flag & 0x100)
			npc->ym += 0x15;
		else
			npc->ym += 0x2A;
		
		//Bounce off walls
		if (npc->flag & 1 && npc->xm < 0)
			npc->xm *= -1;
		if (npc->flag & 4 && npc->xm > 0)
			npc->xm *= -1;
		
		//Bounce off ceiling
		if (npc->flag & 2 && npc->ym < 0)
			npc->ym *= -1;
		
		//Bounce off floor
		if (npc->flag & 8)
		{
			PlaySoundObject(45, 1);
			npc->ym = -0x280;
			npc->xm = 2 * npc->xm / 3;
		}
		
		//Play bounce song (and try to clip out of floor if stuck)
		if (npc->flag & 0xD)
		{
			PlaySoundObject(45, 1);
			if (++npc->count2 > 2)
				npc->y -= 1 * 0x200;
		}
		else
		{
			npc->count2 = 0;
		}
		
		//Limit speed
		if (npc->xm < -0x5FF)
			npc->xm = -0x5FF;
		if (npc->xm > 0x5FF)
			npc->xm = 0x5FF;
		if (npc->ym < -0x5FF)
			npc->ym = -0x5FF;
		if (npc->ym > 0x5FF)
			npc->ym = 0x5FF;
	}
	
	//Move
	npc->x += npc->xm;
	npc->y += npc->ym;
	
	//Animate
	npc->ani_wait++;
	
	if (npc->direct == 0)
	{
		if (npc->ani_wait > 2)
		{
			npc->ani_wait = 0;
			if (++npc->ani_no > 5)
				npc->ani_no = 0;
		}
	}
	else
	{
		if (npc->ani_wait > 2)
		{
			npc->ani_wait = 0;
			if (--npc->ani_no < 0)
				npc->ani_no = 5;
		}
	}
	
	//Delete after 500 frames
	if (++npc->count1 > 500 && npc->ani_no == 5 && npc->ani_wait == 2)
		npc->cond = 0;
}

void Npc001_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[6] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
		{32, 0, 48, 16},
		{48, 0, 64, 16},
		{64, 0, 80, 16},
		{80, 0, 96, 16},
	};
	
	if (!(npc->count1 > 400 && npc->count1 / 2 % 2))
	{
		LoadTLUT_CI4(npc_exp_tlut);
		switch (npc->exp)
		{
			default:
				LoadTex_CI4(96, 16, npc_exp_tex + (48 * 16) * 0);
				break;
			case 5:
				LoadTex_CI4(96, 16, npc_exp_tex + (48 * 16) * 1);
				break;
			case 20:
				LoadTex_CI4(96, 16, npc_exp_tex + (48 * 16) * 2);
				break;
		}
		PutBitmap(&rect[npc->ani_no], x, y);
	}
}

//NPC 003 - Value View Holder
void Npc003_Act(NPCHAR *npc)
{
	if (++npc->count1 > 100)
		npc->cond = 0;
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

//NPC 012 - Balrog (cutscene)
#include "data/bitmap/npc_balrog.inc.c"

void Npc012_Act(NPCHAR *npc)
{
	s32 i;
	s32 x, y;
	
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			if (npc->direct == 4)
			{
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
			}
			
			npc->act_no = 1;
			npc->ani_no = 0;
			//Fallthrough
		case 1:
			if (Random(0, 100) == 0)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 1;
			}
			break;
			
		case 2:
			if (++npc->act_wait > 16)
			{
				npc->act_no = 1;
				npc->ani_no = 0;
			}
			break;
			
		case 10:
			if (npc->direct == 4)
			{
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
			}
			
			npc->act_no = 11;
			npc->ani_no = 2;
			npc->act_wait = 0;
			npc->tgt_x = 0;
			//Fallthrough
		case 11:
			if (++npc->act_wait > 30)
			{
				npc->act_no = 12;
				npc->act_wait = 0;
				npc->ani_no = 3;
				npc->ym = -0x800;
				npc->bits |= NPC_IGNORE_SOLIDITY;
			}
			break;
			
		case 12:
			if (npc->flag & 5)
				npc->xm = 0;
			
			if (npc->y < 0)
			{
				npc->code_char = 0;
				PlaySoundObject(26, 1);
				SetQuake(30);
			}
			break;
			
		case 20:
			if (npc->direct == 4)
			{
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
			}
			
			npc->act_no = 21;
			npc->ani_no = 5;
			npc->act_wait = 0;
			npc->count1 = 0;
			
			for (i = 0; i < 4; ++i)
				SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			
			PlaySoundObject(72, 1);
			//Fallthrough
		case 21:
			npc->tgt_x = 1;
			
			if (npc->flag & 8)
				++npc->act_wait;
			
			if (++npc->count1 / 2 % 2)
				npc->x += 1 * 0x200;
			else
				npc->x -= 1 * 0x200;
			
			if (npc->act_wait > 100)
			{
				npc->act_no = 11;
				npc->act_wait = 0;
				npc->ani_no = 2;
			}
			
			npc->ym += 0x20;
			if (npc->ym > 0x5FF)
				npc->ym = 0x5FF;
			break;
			
		case 30:
			npc->ani_no = 4;
			if (++npc->act_wait > 100)
			{
				npc->act_no = 0;
				npc->ani_no = 0;
			}
			break;
			
		case 40:
			if (npc->direct == 4)
			{
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
			}
			
			npc->act_no = 41;
			npc->act_wait = 0;
			npc->ani_no = 5;
			//Fallthrough
		case 41:
			if (++npc->ani_wait / 2 % 2)
				npc->ani_no = 5;
			else
				npc->ani_no = 6;
			break;
			
		case 42:
			if (npc->direct == 4)
			{
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
			}
			
			npc->act_no = 43;
			npc->act_wait = 0;
			npc->ani_no = 6;
			//Fallthrough
		case 43:
			if (++npc->ani_wait / 2 % 2)
				npc->ani_no = 7;
			else
				npc->ani_no = 6;
			break;
			
		case 50:
			npc->ani_no = 8;
			npc->xm = 0;
			break;
			
		case 60:
			npc->act_no = 61;
			npc->ani_no = 9;
			npc->ani_wait = 0;
			//Fallthrough
		case 61:
			if (++npc->ani_wait > 3)
			{
				npc->ani_wait = 0;
				if (++npc->ani_no == 10 || npc->ani_no == 11)
					PlaySoundObject(23, 1);
			}
			if (npc->ani_no > 12)
				npc->ani_no = 9;
			
			if (npc->direct == 0)
				npc->xm = -0x200;
			else
				npc->xm = 0x200;
			break;
			
		case 70:
			npc->act_no = 71;
			npc->act_wait = 64;
			PlaySoundObject(29, 1);
			npc->ani_no = 13;
			//Fallthrough
		case 71:
			if (--npc->act_wait == 0)
				npc->cond = 0;
			break;
			
		case 80:
			npc->count1 = 0;
			npc->act_no = 81;
			//Fallthrough
		case 81:
			if (++npc->count1 / 2 % 2)
				npc->x += 1 * 0x200;
			else
				npc->x -= 1 * 0x200;
			npc->ani_no = 5;
			npc->xm = 0;
			npc->ym += 0x20;
			break;
			
		case 100:
			npc->act_no = 101;
			npc->act_wait = 0;
			npc->ani_no = 2;
			//Fallthrough
		case 101:
			if (++npc->act_wait > 20)
			{
				npc->act_no = 102;
				npc->act_wait = 0;
				npc->ani_no = 3;
				npc->ym = -0x800;
				npc->bits |= NPC_IGNORE_SOLIDITY;
				DeleteNpCharCode(150, FALSE);
				DeleteNpCharCode(117, FALSE);
				SetNpChar(355, 0, 0, 0, 0, 0, npc, 0x100);
				SetNpChar(355, 0, 0, 0, 0, 1, npc, 0x100);
			}
			break;
			
		case 102:
		{
			x = npc->x / 0x200 / 0x10;
			y = npc->y / 0x200 / 0x10;
			
			if (y >= 0 && y < 35 && ChangeMapParts(x, y, 0))
			{
				ChangeMapParts(x - 1, y, 0);
				ChangeMapParts(x + 1, y, 0);
				PlaySoundObject(44, 1);
				SetQuake2(10);
			}
			
			if (npc->y < -32 * 0x200)
			{
				npc->code_char = 0;
				SetQuake(30);
			}
			break;
		}
	}
	
	//Create smoke
	if (npc->tgt_x && Random(0, 10) == 0)
		SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
	
	//Move
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc012_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const s32 frame[] = {
		0/40,
		160/40,
		80/40,
		120/40,
		240/40,
		200/40,
		280/40,
		0/40,
		8+80/40, 
		8+0/40,
		0/40,
		8+40/40, 
		0/40,
		280/40,
	};
	
	RECT rect;
	if (npc->ani_no != 7)
	{
		if (npc->act_no == 71)
		{
			rect.left += ((npc->direct != 0) ? 40 : 0) + (npc->act_wait % 2);
			rect.top = 0;
			rect.right = ((npc->direct != 0) ? 80 : 40);
			rect.bottom = npc->act_wait / 2;
		}
		else
		{
			rect.left = (npc->direct != 0) ? 40 : 0;
			rect.top = 0;
			rect.right = ((npc->direct != 0) ? 80 : 40);
			rect.bottom = 24;
		}
		LoadTLUT_CI4(npc_balrog_tlut);
		LoadTex_CI4(80, 24, npc_balrog_tex + (40 * 24) * frame[npc->ani_no]);
		PutBitmap(&rect, x, y);
	}
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

//NPC 019 - Balrog (burst)
void Npc019_Act(NPCHAR *npc)
{
	s32 i;
	
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			for (i = 0; i < 0x10; ++i)
				SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			npc->y += 10 * 0x200;
			npc->act_no = 1;
			npc->ani_no = 3;
			npc->ym = -0x100;
			PlaySoundObject(12, 1);
			PlaySoundObject(26, 1);
			SetQuake(30);
			//Fallthrough
		case 1:
			npc->ym += 0x10;
			if (npc->ym > 0 && npc->flag & 8)
			{
				npc->act_no = 2;
				npc->ani_no = 2;
				npc->act_wait = 0;
				PlaySoundObject(26, 1);
				SetQuake(30);
			}
			break;
			
		case 2:
			if (++npc->act_wait > 0x10)
			{
				npc->act_no = 3;
				npc->ani_no = 0;
				npc->ani_wait = 0;
			}
			break;
			
		case 3:
			if (Random(0, 100) == 0)
			{
				npc->act_no = 4;
				npc->act_wait = 0;
				npc->ani_no = 1;
			}
			break;
			
		case 4:
			if (++npc->act_wait > 0x10)
			{
				npc->act_no = 3;
				npc->ani_no = 0;
			}
			break;
	}
	
	//Move
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	if (npc->ym < -0x5FF)
		npc->ym = -0x5FF;
	
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc019_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const s32 frame[] = {
		0/40,
		160/40,
		80/40,
		120/40,
	};
	static const RECT rect[2] = {
		{ 0, 0, 40, 24},
		{40, 0, 80, 24},
	};
	
	LoadTLUT_CI4(npc_balrog_tlut);
	LoadTex_CI4(80, 24, npc_balrog_tex + (40 * 24) * frame[npc->ani_no]);
	PutBitmap(&rect[npc->direct != 0], x, y);
}
