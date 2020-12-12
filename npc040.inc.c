//NPC 041 - Busted door
#include "data/bitmap/npc_busteddoor.inc.c"

void Npc041_Act(NPCHAR *npc)
{
	if (npc->act_no == 0)
	{
		npc->act_no++;
		npc->y -= 1 * 0x10 * 0x200;
	}
}

void Npc041_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 48, 32};
	LoadTLUT_CI4(npc_busteddoor_tlut);
	LoadTex_CI4(48, 32, npc_busteddoor_tex);
	PutBitmap(&rect, x, y);
}

//NPC 042 - Sue
#include "data/bitmap/npc_sue.inc.c"

void Npc042_Act(NPCHAR *npc)
{
	s32 n;
	
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
			
		case 3:
			npc->act_no = 4;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			//Fallthrough
		case 4:
			if (++npc->ani_wait > 4)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 5)
				npc->ani_no = 2;
			
			if (npc->direct == 0)
				npc->xm = -0x200;
			else
				npc->xm = 0x200;
			break;
			
		case 5:
			npc->ani_no = 6;
			npc->xm = 0;
			break;
			
		case 6:
			PlaySoundObject(50, 1);
			npc->act_wait = 0;
			npc->act_no = 7;
			npc->ani_no = 7;
			//Fallthrough
		case 7:
			if (++npc->act_wait > 10)
				npc->act_no = 0;
			break;
			
		case 8:
			PlaySoundObject(50, 1);
			npc->act_wait = 0;
			npc->act_no = 9;
			npc->ani_no = 7;
			npc->ym = -0x200;
			
			if (npc->direct == 0)
				npc->xm = 0x400;
			else
				npc->xm = -0x400;
			//Fallthrough
		case 9:
			if (++npc->act_wait > 3 && npc->flag & 8)
			{
				npc->act_no = 10;
				if (npc->direct == 0)
					npc->direct = 2;
				else
					npc->direct = 0;
			}
			break;
			
		case 10:
			npc->xm = 0;
			npc->ani_no = 8;
			break;
			
		case 11:
			npc->act_no = 12;
			npc->act_wait = 0;
			npc->ani_no = 9;
			npc->ani_wait = 0;
			npc->xm = 0;
			//Fallthrough
		case 12:
			if (++npc->ani_wait > 8)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 10)
				npc->ani_no = 9;
			break;
			
		case 13:
			npc->ani_no = 11;
			npc->xm = 0;
			npc->ym = 0;
			npc->act_no = 14;
			
			for (n = 0; n < NPC_MAX; ++n)
				if (gNPC[n].code_event == 501)
					break;
			
			if (n == NPC_MAX)
			{
				npc->act_no = 0;
				break;
			}
			
			npc->pNpc = &gNPC[n];
			//Fallthrough
		case 14:
			if (npc->pNpc->direct == 0)
				npc->direct = 2;
			else
				npc->direct = 0;
			
			if (npc->pNpc->direct == 0)
				npc->x = npc->pNpc->x - (6 * 0x200);
			else
				npc->x = npc->pNpc->x + (6 * 0x200);
			npc->y = npc->pNpc->y + (4 * 0x200);
			
			if (npc->pNpc->ani_no == 2 || npc->pNpc->ani_no == 4)
				npc->y -= 1 * 0x200;
			break;
			
		case 15:
			npc->act_no = 16;
			SetNpChar(257, npc->x + (128 * 0x200), npc->y, 0, 0, 0, NULL, 0);
			SetNpChar(257, npc->x + (128 * 0x200), npc->y, 0, 0, 2, NULL, 0x80);
			npc->xm = 0;
			npc->ani_no = 0;
			//Fallthrough
		case 16:
			gSuperXpos = npc->x - (24 * 0x200);
			gSuperYpos = npc->y - (8 * 0x200);
			break;
			
		case 17:
			npc->xm = 0;
			npc->ani_no = 12;
			gSuperXpos = npc->x;
			gSuperYpos = npc->y - (8 * 0x200);
			break;
			
		case 20:
			npc->act_no = 21;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			//Fallthrough
		case 21:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			
			if (npc->ani_no > 5)
				npc->ani_no = 2;
			
			if (npc->direct == 0)
				npc->xm = -0x400;
			else
				npc->xm = 0x400;
			
			if (npc->x < gMC.x - (8 * 0x200))
			{
				npc->direct = 2;
				npc->act_no = 0;
			}
			break;
			
		case 30:
			npc->act_no = 31;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			//Fallthrough
		case 31:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 5)
				npc->ani_no = 2;
			
			if (npc->direct == 0)
				npc->xm = -0x400;
			else
				npc->xm = 0x400;
			break;
			
		case 40:
			npc->act_no = 41;
			npc->ani_no = 9;
			npc->ym = -0x400;
			break;
	}
	
	//Fall and move
	if (npc->act_no != 14)
	{
		npc->ym += 0x40;
		
		if (npc->xm > 0x400)
			npc->xm = 0x400;
		if (npc->xm < -0x400)
			npc->xm = -0x400;
		if (npc->ym > 0x5FF)
			npc->ym = 0x5FF;
		
		npc->x += npc->xm;
		npc->y += npc->ym;
	}
}

void Npc042_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{  0, 0,  16, 16},
		{ 16, 0,  32, 16},
		{ 32, 0,  48, 16},
		{  0, 0,  16, 16},
		{ 48, 0,  64, 16},
		{  0, 0,  16, 16},
		{ 64, 0,  80, 16},
		{ 80, 0,  96, 16},
		{ 96, 0, 112, 16},
		{128, 0, 144, 16},
		{  0, 0,  16, 16},
		{112, 0, 128, 16},
		{160, 0, 176, 16},
	};
	LoadTLUT_CI4(npc_sue_tlut);
	LoadTex_CI4(176, 16, npc_sue_tex + (88 * 16) * (npc->direct != 0));
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 043 - Chalkboard
#include "data/bitmap/npc_chalkboard.inc.c"

void Npc043_Act(NPCHAR *npc)
{
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->y -= 1 * 0x10 * 0x200;
			break;
	}
}

void Npc043_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 40, 32},
		{40, 0, 80, 32},
	};
	
	LoadTLUT_CI4(npc_chalkboard_tlut);
	LoadTex_CI4(80, 32, npc_chalkboard_tex);
	PutBitmap(&rect[npc->direct != 0], x, y);
}

//NPC 046 - H/V trigger
void Npc046_Act(NPCHAR *npc)
{
	//Force 'event when touched' flag and move towards player's position
	npc->bits |= NPC_EVENT_WHEN_TOUCHED;
	
	if (npc->direct == 0)
	{
		if (npc->x < gMC.x)
			npc->x += 0x5FF;
		else
			npc->x -= 0x5FF;
	}
	else
	{
		if (npc->y < gMC.y)
			npc->y += 0x5FF;
		else
			npc->y -= 0x5FF;
	}
}

//NPC 058 - Basu
#include "data/bitmap/npc_basu.inc.c"

void Npc058_Act(NPCHAR *npc)
{
	u8 deg;
	s32 xm, ym;
	
	//Move
	switch (npc->act_no)
	{
		case 0:
			if (gMC.x < npc->x + (16 * 0x200) && gMC.x > npc->x - (16 * 0x200))
			{
				npc->bits |= NPC_SHOOTABLE;
				npc->ym = -0x100;
				npc->tgt_x = npc->x;
				npc->tgt_y = npc->y;
				npc->act_no = 1;
				npc->act_wait = 0;
				npc->count1 = npc->direct;
				npc->count2 = 0;
				npc->damage = 6;
				
				if (npc->direct == 0)
				{
					npc->x = gMC.x + (16 * 0x10 * 0x200);
					npc->xm = -0x2FF;
				}
				else
				{
					npc->x = gMC.x - (16 * 0x10 * 0x200);
					npc->xm = 0x2FF;
				}
				
				return;
			}
			
			npc->damage = 0;
			npc->xm = 0;
			npc->ym = 0;
			npc->bits &= ~NPC_SHOOTABLE;
			return;
			
		case 1:
			if (npc->x > gMC.x)
			{
				npc->direct = 0;
				npc->xm -= 0x10;
			}
			else
			{
				npc->direct = 2;
				npc->xm += 0x10;
			}
			
			if (npc->flag & 1)
				npc->xm = 0x200;
			if (npc->flag & 4)
				npc->xm = -0x200;
			
			if (npc->y < npc->tgt_y)
				npc->ym += 8;
			else
				npc->ym -= 8;
			
			if (npc->xm > 0x2FF)
				npc->xm = 0x2FF;
			if (npc->xm < -0x2FF)
				npc->xm = -0x2FF;
			
			if (npc->ym > 0x100)
				npc->ym = 0x100;
			if (npc->ym < -0x100)
				npc->ym = -0x100;
			
			if (npc->shock)
			{
				npc->x += npc->xm / 2;
				npc->y += npc->ym / 2;
			}
			else
			{
				npc->x += npc->xm;
				npc->y += npc->ym;
			}
			
			if (gMC.x > npc->x + (400 * 0x200) || gMC.x < npc->x - (400 * 0x200))
			{
				npc->act_no = 0;
				npc->xm = 0;
				npc->direct = npc->count1;
				npc->x = npc->tgt_x;
				npc->damage = 0;
				return;
			}
			break;
	}

	if (npc->act_no != 0)
	{
		if (npc->act_wait < 150)
			npc->act_wait++;
		
		if (npc->act_wait == 150)
		{
			if ((++npc->count2 % 8) == 0 && npc->x < gMC.x + (160 * 0x200) && npc->x > gMC.x - (160 * 0x200))
			{
				deg = GetArktan(npc->x - gMC.x, npc->y - gMC.y);
				deg += (u8)Random(-6, 6);
				ym = GetSin(deg) * 2;
				xm = GetCos(deg) * 2;
				SetNpChar(84, npc->x, npc->y, xm, ym, 0, NULL, 0x100);
				PlaySoundObject(39, 1);
			}
			
			if (npc->count2 > 8)
			{
				npc->act_wait = 0;
				npc->count2 = 0;
			}
		}
	}
	
	//Animate
	if (++npc->ani_wait > 1)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 1)
		npc->ani_no = 0;
	
	//Blink when firing
	if (npc->act_wait > 120 && npc->act_wait / 2 % 2 == 1 && npc->ani_no == 1)
		npc->ani_no = 2;
}

void Npc058_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][3] = {
		{
			{ 0, 0, 24, 24},
			{24, 0, 48, 24},
			{48, 0, 72, 24},
		},
		{
			{ 0, 24, 24, 48},
			{24, 24, 48, 48},
			{48, 24, 72, 48},
		}
	};
	
	if (npc->act_no != 0)
	{
		LoadTLUT_CI4(npc_basu_tlut);
		LoadTex_CI4(80, 48, npc_basu_tex);
		PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
	}
}

//NPC 059 - Eye Door
#include "data/bitmap/npc_eyedoor.inc.c"

void Npc059_Act(NPCHAR *npc)
{
	//Movement and animation
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			//Fallthrough
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
