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

//NPC 083 - Igor (cutscene)
#include "data/bitmap/npc_igor.inc.c"

void Npc083_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->xm = 0;
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			//Fallthrough
		case 1:
			if (++npc->ani_wait > 5)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 1)
				npc->ani_no = 0;
			break;
			
		case 2:
			npc->act_no = 3;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			//Fallthrough
		case 3:
			if (++npc->ani_wait > 3)
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
			
		case 4:
			npc->xm = 0;
			npc->act_no = 5;
			npc->act_wait = 0;
			npc->ani_no = 6;
			//Fallthrough
		case 5:
			if (++npc->act_wait > 10)
			{
				npc->act_wait = 0;
				npc->act_no = 6;
				npc->ani_no = 7;
				PlaySoundObject(70, 1);
			}
			break;
			
		case 6:
			if (++npc->act_wait > 8)
			{
				npc->act_no = 0;
				npc->ani_no = 0;
			}
			break;
			
		case 7:
			npc->act_no = 1;
			break;
	}
	
	//Fall and move
	npc->ym += 0x40;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc083_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const s32 frame[] = {
		0/40, 
		40/40,
		80/40,
		0/40,
		120/40,
		0/40,
		160/40,
		200/40,
	};
	
	static const RECT rect[] = {
		{ 0, 0, 40, 40},
		{40, 0, 80, 40},
	};
	
	LoadTLUT_CI4(npc_igor_tlut);
	LoadTex_CI4(80, 40, npc_igor_tex + (40 * 40) * frame[npc->ani_no]);
	PutBitmap(&rect[npc->direct != 0], x, y);
}

//NPC 084 - Basu projectile
#include "data/bitmap/npc_basuprojectile.inc.c"

void Npc084_Act(NPCHAR *npc)
{
	//Delete when hitting a wall
	if (npc->flag & 0xFF)
	{
		SetCaret(npc->x, npc->y, 2, 0);
		npc->cond = 0;
	}
	
	npc->y += npc->ym;
	npc->x += npc->xm;
	
	//Animate
	if (++npc->ani_wait > 2)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 3)
		npc->ani_no = 0;
	
	//Delete after 300 frames
	if (++npc->count1 > 300)
	{
		SetCaret(npc->x, npc->y, 2, 0);
		npc->cond = 0;
	}
}

void Npc084_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0,  0, 16, 16},
		{16,  0, 32, 16},
		{ 0, 16, 16, 32},
		{16, 16, 32, 32},
	};
	
	LoadTLUT_CI4(npc_basuprojectile_tlut);
	LoadTex_CI4(32, 32, npc_basuprojectile_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 085 - Terminal
#include "data/bitmap/npc_terminal.inc.c"

void Npc085_Act(NPCHAR *npc)
{
	//Animate
	switch(npc->act_no)
	{
		case 0:
			npc->ani_no = 0;
			if (npc->x - (8 * 0x200) < gMC.x && npc->x + (8 * 0x200) > gMC.x && npc->y - (16 * 0x200) < gMC.y && npc->y + (8 * 0x200) > gMC.y)
			{
				PlaySoundObject(43, 1);
				npc->act_no = 1;
			}
			break;
			
		case 1:
			if (++npc->ani_no > 2)
				npc->ani_no = 1;
			break;
	}
}

void Npc085_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][3] = {
		{
			{ 0, 0, 16, 24},
			{ 0, 0, 16, 24},
			{16, 0, 32, 24},
		},
		{
			{ 0, 0, 16, 24},
			{32, 0, 48, 24},
			{48, 0, 64, 24},
		}
	};
	
	LoadTLUT_CI4(npc_terminal_tlut);
	LoadTex_CI4(64, 24, npc_terminal_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//NPC 086 - Missile
#include "data/bitmap/npc_missile.inc.c"

void Npc086_Act(NPCHAR *npc)
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

void Npc086_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect1[2] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
	};
	static const RECT rect3[2] = {
		{32, 0, 48, 16},
		{48, 0, 64, 16},
	};
	static const RECT rcLast = {64, 0, 80, 16};
	
	if (npc->count1 > 547)
	{
		LoadTLUT_CI4(npc_missile_tlut);
		LoadTex_CI4(80, 16, npc_missile_tex);
		PutBitmap(&rcLast, x, y);
	}
	else if (!(npc->count1 > 500 && npc->count1 / 2 % 2))
	{
		LoadTLUT_CI4(npc_missile_tlut);
		LoadTex_CI4(80, 16, npc_missile_tex);
		switch (npc->exp)
		{
			case 1:
				PutBitmap(&rect1[npc->ani_no], x, y);
				break;
			case 3:
				PutBitmap(&rect3[npc->ani_no], x, y);
				break;
		}
	}
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
	static const RECT rect2[2] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
	};
	static const RECT rect6[2] = {
		{32, 0, 48, 16},
		{48, 0, 64, 16},
	};
	static const RECT rcLast = {64, 0, 80, 16};
	
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

//NPC 088 - Igor (boss)
void Npc088_Act(NPCHAR *npc)
{
	s32 i;
	u8 deg;
	s32 xm, ym;

	switch (npc->act_no)
	{
		case 0:
			npc->xm = 0;
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			//Fallthrough
		case 1:
			if (++npc->ani_wait > 5)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 1)
				npc->ani_no = 0;
			
			if (++npc->act_wait > 50)
				npc->act_no = 2;
			break;
			
		case 2:
			npc->act_no = 3;
			npc->act_wait = 0;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			
			if (++npc->count1 < 3 || npc->life > 150)
			{
				npc->count2 = 0;
				
				if (gMC.x < npc->x)
					npc->direct = 0;
				else
					npc->direct = 2;
			}
			else
			{
				npc->count2 = 1;

				if (gMC.x < npc->x)
					npc->direct = 2;
				else
					npc->direct = 0;
			}
			//Fallthrough
		case 3:
			++npc->act_wait;
			
			if (++npc->ani_wait > 3)
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
			
			if (npc->count2)
			{
				if (npc->act_wait > 16)
				{
					npc->act_no = 9;
					npc->xm = 0;
					npc->ani_no = 10;
					break;
				}
			}
			else if (npc->act_wait > 50)
			{
				npc->ani_no = 8;
				npc->ym = -0x400;
				npc->act_no = 7;
				npc->act_wait = 0;
				npc->xm = (npc->xm * 3) / 2;
				npc->damage = 2;
				break;
			}
			else
			{
				if (npc->direct == 0)
				{
					if (npc->x - (24 * 0x200) < gMC.x)
						npc->act_no = 4;
				}
				else
				{
					if (npc->x + (24 * 0x200) > gMC.x)
						npc->act_no = 4;
				}
			}
			break;
			
		case 4:
			npc->xm = 0;
			npc->act_no = 5;
			npc->act_wait = 0;
			npc->ani_no = 6;
			//Fallthrough
		case 5:
			if (++npc->act_wait > 12)
			{
				npc->act_wait = 0;
				npc->act_no = 6;
				npc->ani_no = 7;
				PlaySoundObject(70, 1);
				npc->damage = 5;
				npc->hit.front = 24 * 0x200;
				npc->hit.top = 1;
			}
			break;
			
		case 6:
			if (++npc->act_wait > 10)
			{
				npc->act_no = 0;
				npc->ani_no = 0;
				npc->damage = 0;
				npc->hit.front = 8 * 0x200;
				npc->hit.top = 16 * 0x200;
			}
			break;
			
		case 7:
			if (npc->flag & 8)
			{
				npc->act_no = 8;
				npc->ani_no = 9;
				PlaySoundObject(26, 1);
				SetQuake(30);
				npc->damage = 0;
				
				for (i = 0; i < 4; i++)
					SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			}
			break;
			
		case 8:
			npc->xm = 0;
			
			if (++npc->act_wait > 10)
			{
				npc->act_no = 0;
				npc->ani_no = 0;
				npc->damage = 0;
			}
			break;
			
		case 9:
			npc->act_no = 10;
			npc->act_wait = 0;
			
			if (gMC.x < npc->x)
				npc->direct = 0;
			else
				npc->direct = 2;
			//Fallthrough
		case 10:
			if (++npc->act_wait > 100 && npc->act_wait % 6 == 1)
			{
				if (npc->direct == 0)
					deg = 0x88;
				else
					deg = 0xF8;
				
				deg += (u8)Random(-0x10, 0x10);
				ym = GetSin(deg) * 3;
				xm = GetCos(deg) * 3;
				SetNpChar(11, npc->x, npc->y + (4 * 0x200), xm, ym, 0, NULL, 0x100);
				
				PlaySoundObject(12, 1);
			}
			
			if (npc->act_wait > 50 && npc->act_wait / 2 % 2)
				npc->ani_no = 11;
			else
				npc->ani_no = 10;
			
			if (npc->act_wait > 132)
			{
				npc->act_no = 0;
				npc->ani_no = 0;
				npc->count1 = 0;
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

void Npc088_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const s32 frame[] = {
		0/40,
		40/40,
		80/40,
		0/40,
		120/40,
		0/40,
		160/40,
		200/40,
		8+0/40,
		8+40/40,
		240/40,
		280/40,
	};
	
	static const RECT rect[] = {
		{ 0, 0, 40, 40},
		{40, 0, 80, 40},
	};
	
	LoadTLUT_CI4(npc_igor_tlut);
	LoadTex_CI4(80, 40, npc_igor_tex + (40 * 40) * frame[npc->ani_no]);
	PutBitmap(&rect[npc->direct != 0], x, y);
}

//NPC 089 - Igor (dead)
#include "data/bitmap/npc_igordead.inc.c"

void Npc089_Act(NPCHAR *npc)
{
	s32 i;
	
	switch (npc->act_no)
	{
		case 0:
			PlaySoundObject(72, 1);
			
			if (npc->x > gMC.x)
				npc->direct = 0;
			else
				npc->direct = 2;
			
			for (i = 0; i < 8; i++)
				SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			
			npc->act_no = 1;
			//Fallthrough
		case 1:
			if (++npc->act_wait > 100)
			{
				npc->act_wait = 0;
				npc->act_no = 2;
			}
			
			if (npc->act_wait % 5 == 0)
				SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			break;
			
		case 2:
			if (++npc->act_wait / 2 % 2 && npc->act_wait < 100)
			{
				npc->ani_no = 0;
				npc->view.back = 20 * 0x200;
				npc->view.front = 20 * 0x200;
				npc->view.top = 20 * 0x200;
			}
			else
			{
				npc->ani_no = 1;
				npc->view.back = 12 * 0x200;
				npc->view.front = 12 * 0x200;
				npc->view.top = 8 * 0x200;
			}
			
			if (npc->act_wait > 150)
			{
				npc->act_wait = 0;
				npc->act_no = 3;
				npc->ani_no = 1;
			}
			
			if (npc->act_wait % 9 == 0)
				SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			break;
			
		case 3:
			if (++npc->ani_wait > 50)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no == 3)
				npc->act_no = 4;
			break;
	}
	
	//Fall and move
	npc->ym += 0x40;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc089_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][4] = {
		{
			{ 0, 0, 40, 40}, //Regular Igor sheet
			{ 0, 0, 24, 24}, //Igor dead sheet
			{24, 0, 48, 24},
			{48, 0, 72, 24},
		},
		{
			{40, 0, 80, 40}, //Regular Igor sheet
			{ 0, 24, 24, 48}, //Igor dead sheet
			{24, 24, 48, 48},
			{48, 24, 72, 48},
		},
	};
	
	RECT shake_rect;
	
	if (npc->act_no == 1)
	{
		shake_rect.left = ((npc->direct != 0) ? 40 : 0) + (npc->act_wait % 2);
		shake_rect.top = 0;
		shake_rect.right = ((npc->direct != 0) ? 80 : 40);
		shake_rect.bottom = 40;
		LoadTLUT_CI4(npc_igor_tlut);
		LoadTex_CI4(80, 40, npc_igor_tex + (40 * 400));
		PutBitmap(&shake_rect, x, y);
	}
	else
	{
		if (npc->ani_no == 0)
		{
			LoadTLUT_CI4(npc_igor_tlut);
			LoadTex_CI4(80, 40, npc_igor_tex + (40 * 400));
		}
		else
		{
			LoadTLUT_CI4(npc_igordead_tlut);
			LoadTex_CI4(80, 48, npc_igordead_tex);
		}
		PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
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

//NPC 092 - Sue at Computer
#include "data/bitmap/npc_computersue.inc.c"

void Npc092_Act(NPCHAR *npc)
{
	//Animate
	switch (npc->act_no)
	{
		case 0:
			npc->x -= 4 * 0x200;
			npc->y += 16 * 0x200;
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			//Fallthrough
		case 1:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 1)
				npc->ani_no = 0;
			
			if (Random(0, 80) == 1)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 1;
			}
			if (Random(0, 120) == 10)
			{
				npc->act_no = 3;
				npc->act_wait = 0;
				npc->ani_no = 2;
			}
			break;
			
		case 2:
			if (++npc->act_wait > 40)
			{
				npc->act_no = 3;
				npc->act_wait = 0;
				npc->ani_no = 2;
			}
			break;
			
		case 3:
			if (++npc->act_wait > 80)
			{
				npc->act_no = 1;
				npc->ani_no = 0;
			}
			break;
	}
}

void Npc092_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 24},
		{16, 0, 32, 24},
		{32, 0, 48, 24},
	};
	
	LoadTLUT_CI4(npc_computersue_tlut);
	LoadTex_CI4(48, 24, npc_computersue_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 093 - Chaco
#include "data/bitmap/npc_chaco.inc.c"

void Npc093_Act(NPCHAR *npc)
{
	//Move and animate
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
			
			if (npc->x - (32 * 0x200) < gMC.x && npc->x + (32 * 0x200) > gMC.x && npc->y - (32 * 0x200) < gMC.y && npc->y + (16 * 0x200) > gMC.y)
			{
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
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
				npc->x -= 1 * 0x200;
			else
				npc->x += 1 * 0x200;
			break;
			
		case 10:
			npc->ani_no = 6;
			
			if (++npc->act_wait > 200)
			{
				npc->act_wait = 0;
				SetCaret(npc->x, npc->y, 5, 0);
			}
			break;
	}
}

void Npc093_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][7] = {
		{
			{ 0, 0, 16, 16},
			{16, 0, 32, 16},
			{32, 0, 48, 16},
			{ 0, 0, 16, 16},
			{48, 0, 64, 16},
			{ 0, 0, 16, 16},
			{64, 0, 80, 16},
		},
		{
			{ 0, 16, 16, 32},
			{16, 16, 32, 32},
			{32, 16, 48, 32},
			{ 0, 16, 16, 32},
			{48, 16, 64, 32},
			{ 0, 16, 16, 32},
			{64,  0, 80, 16},
		}
	};
	
	LoadTLUT_CI4(npc_chaco_tlut);
	LoadTex_CI4(80, 32, npc_chaco_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//NPC 094 - Kulala
#include "data/bitmap/npc_kulala.inc.c"

void Npc094_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->ani_no = 4;
			
			if (npc->shock)
			{
				npc->ani_no = 0;
				npc->act_no = 10;
				npc->act_wait = 0;
			}
			break;
			
		case 10:
			npc->bits |= NPC_SHOOTABLE;
			npc->bits &= ~NPC_INVULNERABLE;
			
			if (++npc->act_wait > 40)
			{
				npc->act_wait = 0;
				npc->ani_wait = 0;
				npc->act_no = 11;
			}
			break;
			
		case 11:
			if (++npc->ani_wait > 5)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 2)
			{
				npc->act_no = 12;
				npc->ani_no = 3;
			}
			break;
			
		case 12:
			npc->ym = -0x155;
			
			if (++npc->act_wait > 20)
			{
				npc->act_wait = 0;
				npc->act_no = 10;
				npc->ani_no = 0;
			}
			break;
			
		case 20:
			npc->xm /= 2;
			npc->ym += 0x20;
			
			if (npc->shock == 0)
			{
				npc->act_wait = 30;
				npc->act_no = 10;
				npc->ani_no = 0;
			}
			break;
	}
	
	//Handle invulnerability
	if (npc->shock)
	{
		if (++npc->count2 > 12)
		{
			npc->act_no = 20;
			npc->ani_no = 4;
			npc->bits &= ~NPC_SHOOTABLE;
			npc->bits |= NPC_INVULNERABLE;
		}
	}
	else
	{
		npc->count2 = 0;
	}
	
	//Gravity and force towards player
	if (npc->act_no >= 10)
	{
		if (npc->flag & 1)
		{
			npc->count1 = 50;
			npc->direct = 2;
		}
		if (npc->flag & 4)
		{
			npc->count1 = 50;
			npc->direct = 0;
		}
		
		if (npc->count1 != 0)
		{
			npc->count1--;
			
			if (npc->direct == 0)
				npc->xm -= 0x80;
			else
				npc->xm += 0x80;
		}
		else
		{
			npc->count1 = 50;
			
			if (npc->x > gMC.x)
				npc->direct = 0;
			else
				npc->direct = 2;
		}
		
		npc->ym += 0x10;
		if (npc->flag & 8)
			npc->ym = -0x400;
	}
	
	//Limit speed
	if (npc->xm > 0x100)
		npc->xm = 0x100;
	if (npc->xm < -0x100)
		npc->xm = -0x100;
	
	if (npc->ym > 0x300)
		npc->ym = 0x300;
	if (npc->ym < -0x300)
		npc->ym = -0x300;
	
	//Move
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc094_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 48, 24};
	LoadTLUT_CI4(npc_kulala_tlut);
	LoadTex_CI4(48, 24, npc_kulala_tex + (24 * 24) * npc->ani_no);
	PutBitmap(&rect, x, y);
}

//NPC 095 - Jelly
#include "data/bitmap/npc_jelly.inc.c"

void Npc095_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->act_wait = Random(0, 50);
			npc->tgt_y = npc->y;
			npc->tgt_x = npc->x;
			
			if (npc->direct == 0)
				npc->xm = 0x200;
			else
				npc->xm = -0x200;
			//Fallthrough
		case 1:
			if (--npc->act_wait > 0)
				break;
			npc->act_no = 10;
			//Fallthrough
		case 10:
			if (++npc->act_wait > 10)
			{
				npc->act_wait = 0;
				npc->ani_wait = 0;
				npc->act_no = 11;
			}
			break;
			
		case 11:
			if (++npc->ani_wait > 5)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			
			if (npc->ani_no == 2)
			{
				if (npc->direct == 0)
					npc->xm -= 0x100;
				else
					npc->xm += 0x100;
				npc->ym -= 0x200;
			}
			
			if (npc->ani_no > 2)
			{
				npc->act_no = 12;
				npc->ani_no = 3;
			}
			break;
			
		case 12:
			npc->act_wait++;
			
			if (npc->y > npc->tgt_y && npc->act_wait > 10)
			{
				npc->act_wait = 0;
				npc->act_no = 10;
				npc->ani_no = 0;
			}
			break;
	}
	
	//Turn to face original position
	if (npc->x > npc->tgt_x)
		npc->direct = 0;
	else
		npc->direct = 2;
	
	//Turn around when hit walls
	if (npc->flag & 1)
	{
		npc->count1 = 50;
		npc->direct = 2;
	}
	if (npc->flag & 4)
	{
		npc->count1 = 50;
		npc->direct = 0;
	}
	
	//Gravity
	npc->ym += 0x20;
	if (npc->flag & 8)
		npc->ym = -0x400;
	
	//Limit speed
	if (npc->xm > 0x100)
		npc->xm = 0x100;
	if (npc->xm < -0x100)
		npc->xm = -0x100;
	if (npc->ym > 0x200)
		npc->ym = 0x200;
	if (npc->ym < -0x200)
		npc->ym = -0x200;
	
	//Move
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
}

void Npc095_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][4] = {
		{
			{16, 0, 32, 16},
			{32, 0, 48, 16},
			{48, 0, 64, 16},
			{64, 0, 80, 16},
		},
		{
			{16, 16, 32, 32},
			{32, 16, 48, 32},
			{48, 16, 64, 32},
			{64, 16, 80, 32},
		}
	};
	
	LoadTLUT_CI4(npc_jelly_tlut);
	LoadTex_CI4(80, 32, npc_jelly_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//Fans
#include "data/bitmap/npc_fan.inc.c"

void NpcFan_Put(NPCHAR *npc, s32 x, s32 y)
{
	RECT rc;
	rc.left = npc->ani_no << 4;
	rc.top = (npc->code_char - 96) << 4;
	rc.right = rc.left + 16;
	rc.bottom = rc.top + 16;
	
	LoadTLUT_CI4(npc_fan_tlut);
	LoadTex_CI4(48, 64, npc_fan_tex);
	PutBitmap(&rc, x, y);
}

//NPC 096 - Fan (Left)
void Npc096_Act(NPCHAR *npc)
{
	//Blow player
	switch (npc->act_no)
	{
		case 0:
			if (npc->direct == 2)
				npc->act_no = 2;
			else
				npc->ani_no = 1;
			//Fallthrough
		case 1:
			npc->ani_no = 0;
			break;
			
		case 2:
			if (++npc->ani_wait > 0)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 2)
				npc->ani_no = 0;
			
			if (gMC.x > npc->x - (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.x < npc->x + (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.y > npc->y - (((SCREEN_HEIGHT / 2) + 120) * 0x200) && gMC.y < npc->y + (((SCREEN_HEIGHT / 2) + 120) * 0x200))
			{
				if (Random(0, 5) == 1)
					SetNpChar(199, npc->x, npc->y + (Random(-8, 8) * 0x200), 0, 0, 0, NULL, 0x100);
			}
			
			if (gMC.y < npc->y + (8 * 0x200) && gMC.y > npc->y - (8 * 0x200) && gMC.x < npc->x && gMC.x > npc->x - (96 * 0x200))
			{
				gMC.xm -= 0x88;
				gMC.cond |= 0x20;
			}
			break;
	}
}

//NPC 097 - Fan (Up)
void Npc097_Act(NPCHAR *npc)
{
	switch (npc->act_no)
	{
		case 0:
			if (npc->direct == 2)
				npc->act_no = 2;
			else
				npc->ani_no = 1;
			//Fallthrough
		case 1:
			npc->ani_no = 0;
			break;
			
		case 2:
			if (++npc->ani_wait > 0)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 2)
				npc->ani_no = 0;
			
			if (gMC.x > npc->x - (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.x < npc->x + (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.y > npc->y - (((SCREEN_HEIGHT / 2) + 120) * 0x200) && gMC.y < npc->y + (((SCREEN_HEIGHT / 2) + 120) * 0x200))
			{
				if (Random(0, 5) == 1)
					SetNpChar(199, npc->x + (Random(-8, 8) * 0x200), npc->y, 0, 0, 1, NULL, 0x100);
			}
			
			if (gMC.x < npc->x + (8 * 0x200) && gMC.x > npc->x - (8 * 0x200) && gMC.y < npc->y && gMC.y > npc->y - (96 * 0x200))
				gMC.ym -= 0x88;
			break;
	}
}

//NPC 098 - Fan (Right)
void Npc098_Act(NPCHAR *npc)
{
	switch (npc->act_no)
	{
		case 0:
			if (npc->direct == 2)
				npc->act_no = 2;
			else
				npc->ani_no = 1;
			//Fallthrough
		case 1:
			npc->ani_no = 0;
			break;
		
		case 2:
			if (++npc->ani_wait > 0)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 2)
				npc->ani_no = 0;
			
			if (gMC.x > npc->x - (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.x < npc->x + (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.y > npc->y - (((SCREEN_HEIGHT / 2) + 120) * 0x200) && gMC.y < npc->y + (((SCREEN_HEIGHT / 2) + 120) * 0x200))
			{
				if (Random(0, 5) == 1)
					SetNpChar(199, npc->x, npc->y + (Random(-8, 8) * 0x200), 0, 0, 2, NULL, 0x100);
			}
			
			if (gMC.y < npc->y + (8 * 0x200) && gMC.y > npc->y - (8 * 0x200) && gMC.x < npc->x + (96 * 0x200) && gMC.x > npc->x)
			{
				gMC.xm += 0x88;
				gMC.cond |= 0x20;
			}
			break;
	}
}

//NPC 099 - Fan (Down)
void Npc099_Act(NPCHAR *npc)
{
	switch (npc->act_no)
	{
		case 0:
			if (npc->direct == 2)
				npc->act_no = 2;
			else
				npc->ani_no = 1;
			//Fallthrough
		case 1:
			npc->ani_no = 0;
			break;
			
		case 2:
			if (++npc->ani_wait > 0)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 2)
				npc->ani_no = 0;
			
			if (gMC.x > npc->x - (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.x < npc->x + (((SCREEN_WIDTH / 2) + 160) * 0x200) && gMC.y > npc->y - (((SCREEN_HEIGHT / 2) + 120) * 0x200) && gMC.y < npc->y + (((SCREEN_HEIGHT / 2) + 120) * 0x200))
			{
				if (Random(0, 5) == 1)
					SetNpChar(199, npc->x + (Random(-8, 8) * 0x200), npc->y, 0, 0, 3, NULL, 0x100);
			}
			
			if (gMC.x < npc->x + (8 * 0x200) && gMC.x > npc->x - (8 * 0x200) && gMC.y < npc->y + (96 * 0x200) && gMC.y > npc->y)
				gMC.ym += 0x88;
			break;
	}
}
