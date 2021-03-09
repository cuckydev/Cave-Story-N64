//NPC 101 - Malco Computer Screen
#include "data/bitmap/npc_malcoscreen.inc.c"

void Npc101_Act(NPCHAR *npc)
{
	//Animate
	if (++npc->ani_wait > 3)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 2)
		npc->ani_no = 0;
}

void Npc101_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[3] = {
		{ 0, 0, 16, 16},
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
	};
	
	LoadTLUT_CI4(npc_malcoscreen_tlut);
	LoadTex_CI4(32, 16, npc_malcoscreen_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 102 - Malco Computer Wave
#include "data/bitmap/npc_malcowave.inc.c"

void Npc102_Act(NPCHAR *npc)
{
	//Move up 8 pixels
	if (npc->act_no == 0)
	{
		npc->act_no = 1;
		npc->y += 8 * 0x200;
	}
	
	//Animate
	if (++npc->ani_wait > 0)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 3)
		npc->ani_no = 0;
}

void Npc102_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[4] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
		{32, 0, 48, 16},
		{48, 0, 64, 16},
	};
	
	LoadTLUT_CI4(npc_malcowave_tlut);
	LoadTex_CI4(64, 16, npc_malcowave_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 103 - Mannan projectile
#include "data/bitmap/npc_mannanprojectile.inc.c"

void Npc103_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			//Fallthrough
		case 1:
			if (npc->direct == 0)
				npc->xm -= 0x20;
			else
				npc->xm += 0x20;
			
			if (++npc->ani_wait > 0)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}
			if (npc->ani_no > 2)
				npc->ani_no = 0;
			break;
	}
	
	npc->x += npc->xm;
	
	//Delete after 100 frames and play sound
	if (++npc->count1 > 100)
		npc->cond = 0;
	if (npc->count1 % 4 == 1)
		PlaySoundObject(46, 1);
}

void Npc103_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][3] = {
		{
			{ 0, 0, 16, 24},
			{16, 0, 32, 24},
			{32, 0, 48, 24},
		},
		{
			{ 0, 24, 16, 48},
			{16, 24, 32, 48},
			{32, 24, 48, 48},
		}
	};
	
	LoadTLUT_CI4(npc_mannanprojectile_tlut);
	LoadTex_CI4(48, 48, npc_mannanprojectile_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//NPC 104 - Frog
#include "data/bitmap/npc_frog.inc.c"

void Npc104_Act(NPCHAR *npc)
{
	BOOL bJump;
	
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->act_wait = 0;
			npc->xm = 0;
			npc->ym = 0;
			
			if (npc->direct == 4)
			{
				if (Random(0, 1))
					npc->direct = 0;
				else
					npc->direct = 2;
				
				npc->bits |= NPC_IGNORE_SOLIDITY;
				npc->ani_no = 2;
				npc->act_no = 3;
				break;
			}
			
			npc->bits &= ~NPC_IGNORE_SOLIDITY;
			//Fallthrough
		case 1:
			npc->act_wait++;
			
			if (Random(0, 50) == 1)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 0;
				npc->ani_wait = 0;
				break;
			}
			break;
			
		case 2:
			npc->act_wait++;
			
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 1)
				npc->ani_no = 0;
			
			if (npc->act_wait > 18)
			{
				npc->act_no = 1;
				npc->act_no = 1;
			}
			break;
			
		case 3:
			if (++npc->act_wait > 40)
				npc->bits &= ~NPC_IGNORE_SOLIDITY;
			
			if (npc->flag & 8)
			{
				npc->act_no = 0;
				npc->ani_no = 0;
				npc->act_wait = 0;
			}
			break;
			
		case 10:
			npc->act_no = 11;
			//Fallthrough
		case 11:
			if (npc->flag & 1 && npc->xm < 0)
			{
				npc->xm *= -1;
				npc->direct = 2;
			}
			if (npc->flag & 4 && npc->xm > 0)
			{
				npc->xm *= -1;
				npc->direct = 0;
			}
			if (npc->flag & 8)
			{
				npc->act_no = 0;
				npc->ani_no = 0;
				npc->act_wait = 0;
			}
			break;
	}
	
	//Check if we should jump
	bJump = FALSE;
	if (npc->act_no < 10 && npc->act_no != 3 && npc->act_wait > 10)
	{
		if (npc->shock)
			bJump = TRUE;
		
		if (!(npc->x < gMC.x - (160 * 0x200) || npc->x > gMC.x + (160 * 0x200) || npc->y < gMC.y - (64 * 0x200) || npc->y > gMC.y + (64 * 0x200)))
		{
			if (Random(0, 50) == 2)
				bJump = TRUE;
		}
	}
	
	//Jump
	if (bJump)
	{
		if (npc->x < gMC.x)
			npc->direct = 2;
		else
			npc->direct = 0;
		
		npc->act_no = 10;
		npc->ani_no = 2;
		npc->ym = -0x5FF;
		
		if (!(gMC.cond & 2))
			PlaySoundObject(30, 1);
		
		if (npc->direct == 0)
			npc->xm = -0x200;
		else
			npc->xm = 0x200;
	}
	
	//Fall and move
	npc->ym += 0x80;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc104_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[3] = {
		{ 0, 0, 32, 32},
		{32, 0, 64, 32},
		{64, 0, 96, 32},
	};
	
	LoadTLUT_CI4(npc_frog_tlut);
	LoadTex_CI4(96, 32, npc_frog_tex + (48 * 32) * (npc->direct != 0));
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 105 - "Hey" bubble
#include "data/bitmap/npc_hey.inc.c"

void Npc105_Act(NPCHAR *npc)
{
	//Move up and despawn after half a second
	if (++npc->act_wait > 30)
		npc->cond = 0;
	if (npc->act_wait < 5)
		npc->y -= 1 * 0x200;
}

void Npc105_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 16, 16};
	
	LoadTLUT_CI4(npc_hey_tlut);
	LoadTex_CI4(16, 16, npc_hey_tex);
	PutBitmap(&rect, x, y);
}

//NPC 106 - "Hey" bubble (spawns 8 pixels higher)
void Npc106_Act(NPCHAR *npc)
{
	switch (npc->act_no)
	{
		case 0:
			SetNpChar(105, npc->x, npc->y - (8 * 0x200), 0, 0, 0, NULL, 0x180);
			npc->act_no = 1;
			break;
	}
}

//NPC 107 - Malco
#include "data/bitmap/npc_malco.inc.c"

void Npc107_Act(NPCHAR *npc)
{
	s32 i;
	
	//Animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			if (npc->direct == 2)
				npc->ani_no = 5;
			break;
			
		case 10:
			npc->act_no = 11;
			npc->act_wait = 0;
			npc->ani_wait = 0;
			for (i = 0; i < 4; i++)
				SetNpChar(4, npc->x, npc->y, Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			//Fallthrough
		case 11:
			if (++npc->ani_wait > 1)
			{
				PlaySoundObject(43, 1);
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 1)
				npc->ani_no = 0;
			
			if (++npc->act_wait > 100)
				npc->act_no = 12;
			break;
			
		case 12:
			npc->act_no = 13;
			npc->act_wait = 0;
			npc->ani_no = 1;
			//Fallthrough
		case 13:
			if (++npc->act_wait > 50)
				npc->act_no = 14;
			break;
			
		case 14:
			npc->act_no = 15;
			npc->act_wait = 0;
			//Fallthrough
		case 15:
			if (npc->act_wait / 2 % 2)
			{
				npc->x += 1 * 0x200;
				PlaySoundObject(11, 1);
			}
			else
			{
				npc->x -= 1 * 0x200;
			}
			
			if (++npc->act_wait > 50)
				npc->act_no = 16;
			break;
			
		case 16:
			npc->act_no = 17;
			npc->act_wait = 0;
			npc->ani_no = 2;
			PlaySoundObject(12, 1);
			for (i = 0; i < 8; i++)
				SetNpChar(4, npc->x, npc->y, Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			//Fallthrough
		case 17:
			if (++npc->act_wait > 150)
				npc->act_no = 18;
			break;
			
		case 18:
			npc->act_no = 19;
			npc->act_wait = 0;
			npc->ani_no = 3;
			npc->ani_wait = 0;
			//Fallthrough
		case 19:
			if (++npc->ani_wait > 3)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 4)
			{
				PlaySoundObject(11, 1);
				npc->ani_no = 3;
			}
			
			if (++npc->act_wait > 100)
			{
				npc->act_no = 20;
				PlaySoundObject(12, 1);
				for (i = 0; i < 4; i++)
					SetNpChar(4, npc->x, npc->y, Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			}
			break;
			
		case 20:
			npc->ani_no = 4;
			break;
			
		case 21:
			npc->act_no = 22;
			npc->ani_no = 5;
			PlaySoundObject(51, 1);
			break;
			
		case 100:
			npc->act_no = 101;
			npc->ani_no = 6;
			npc->ani_wait = 0;
			//Fallthrough
		case 101:
			if (++npc->ani_wait > 4)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 9)
				npc->ani_no = 6;
			break;
			
		case 110:
			SetDestroyNpChar(npc->x, npc->y, 0x2000, 16);
			npc->cond = 0;
			break;
	}
}

void Npc107_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 24},
		{16, 0, 32, 24},
		{32, 0, 48, 24},
		{48, 0, 64, 24},
		{64, 0, 80, 24},
		{80, 0, 96, 24},
		{32, 0, 48, 24},
		{48, 0, 64, 24},
		{64, 0, 80, 24},
		{48, 0, 64, 24},
	};
	
	LoadTLUT_CI4(npc_malco_tlut);
	LoadTex_CI4(128, 24, npc_malco_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 109 - Malco (Broken)
void Npc109_Act(NPCHAR *npc)
{
	s32 i;
	
	//Animate
	switch (npc->act_no)
	{
		case 0:
			if (--npc->act_wait != 0)
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
			
		case 10:
			npc->act_no = 0;
			PlaySoundObject(12, 1);
			for (i = 0; i < 8; i++)
				SetNpChar(4, npc->x, npc->y, Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			break;
	}
	
	//Fall
	npc->ym += 0x40;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	npc->y += npc->ym;
}

void Npc109_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2] = {
		{ 96, 0, 112, 24},
		{112, 0, 128, 24}
	};
	
	LoadTLUT_CI4(npc_malco_tlut);
	LoadTex_CI4(128, 24, npc_malco_tex + (64 * 24) * (npc->direct != 0));
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 111 - Quote teleporting out
#include "data/bitmap/mychar.inc.c"

void Npc111_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->y -= 16 * 0x200;
			break;
			
		case 1:
			if (++npc->act_wait > 20)
			{
				npc->act_wait = 0;
				npc->act_no = 2;
				npc->ani_no = 1;
				npc->ym = -0x2FF;
			}
			break;
			
		case 2:
			if (npc->ym > 0)
				npc->hit.bottom = 16 * 0x200;
			
			if (npc->flag & 8)
			{
				npc->act_no = 3;
				npc->act_wait = 0;
				npc->ani_no = 0;
			}
			break;
			
		case 3:
			if (++npc->act_wait > 40)
			{
				npc->act_no = 4;
				npc->act_wait = 64;
				PlaySoundObject(29, 1);
			}
			break;
			
		case 4:
			npc->act_wait--;
			npc->ani_no = 0;
			if (npc->act_wait == 0)
				npc->cond = 0;
			break;
	}
	
	//Fall and move
	npc->ym += 0x40;
	npc->y += npc->ym;
}

void Npc111_Put(NPCHAR *npc, s32 x, s32 y)
{
	RECT rect;
	
	if (npc->act_no == 4)
	{
		rect.left = npc->act_wait / 2 % 2;
		rect.top = 0;
		rect.right = 16;
		rect.bottom = npc->act_wait / 4;
	}
	else
	{
		rect.left = npc->ani_no ? 16 : 0;
		rect.top = 0;
		rect.right = npc->ani_no ? 32 : 16;
		rect.bottom = 16;
	}
	
	LoadTLUT_CI4(mychar_tlut);
	LoadTex_CI4(176, 16, mychar_tex + (88 * 16) * ((((gMC.equip & EQUIP_MIMIGA_MASK) != 0) * 2) + (npc->direct != 0)));
	PutBitmap(&rect, x, y);
}

//NPC 112 - Quote teleporting in
void Npc112_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			npc->x += 16 * 0x200;
			npc->y += 8 * 0x200;
			PlaySoundObject(29, 1);
			//Fallthrough
		case 1:
			if (++npc->act_wait == 64)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
			}
			break;
			
		case 2:
			if (++npc->act_wait > 20)
			{
				npc->act_no = 3;
				npc->ani_no = 1;
				npc->hit.bottom = 8 * 0x200;
			}
			break;
			
		case 3:
			if (npc->flag & 8)
			{
				npc->act_no = 4;
				npc->act_wait = 0;
				npc->ani_no = 0;
			}
			break;
	}
	
	//Fall and move
	npc->ym += 0x40;
	npc->y += npc->ym;
}

void Npc112_Put(NPCHAR *npc, s32 x, s32 y)
{
	RECT rect;
	
	if (npc->act_no == 1)
	{
		rect.left = npc->act_wait / 2 % 2;
		rect.top = 0;
		rect.right = 16;
		rect.bottom = npc->act_wait / 4;
	}
	else
	{
		rect.left = npc->ani_no ? 16 : 0;
		rect.top = 0;
		rect.right = npc->ani_no ? 32 : 16;
		rect.bottom = 16;
	}
	
	LoadTLUT_CI4(mychar_tlut);
	LoadTex_CI4(176, 16, mychar_tex + (88 * 16) * ((((gMC.equip & EQUIP_MIMIGA_MASK) != 0) * 2) + (npc->direct != 0)));
	PutBitmap(&rect, x, y);
}

//NPC 114 - Press
#include "data/bitmap/npc_press.inc.c"

void Npc114_Act(NPCHAR *npc)
{
	s32 i;
	
	//Animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->y -= 4 * 0x200;
			//Fallthrough
		case 1:
			if (!(npc->flag & 8))
			{
				npc->act_no = 10;
				npc->ani_wait = 0;
				npc->ani_no = 1;
			}
			break;
			
		case 10:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			
			if (npc->ani_no > 2)
				npc->ani_no = 2;
			
			if (gMC.y > npc->y)
			{
				npc->bits &= ~NPC_SOLID_HARD;
				npc->damage = 0x7F;
			}
			else
			{
				npc->bits |= NPC_SOLID_HARD;
				npc->damage = 0;
			}
			
			if (npc->flag & 8)
			{
				if (npc->ani_no > 1)
				{
					for (i = 0; i < 4; i++)
						SetNpChar(4, npc->x, npc->y, Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
					PlaySoundObject(26, 1);
					SetQuake(10);
				}
				
				npc->act_no = 1;
				npc->ani_no = 0;
				npc->damage = 0;
				npc->bits |= NPC_SOLID_HARD;
			}
			break;
	}
	
	//Fall and move
	npc->ym += 0x20;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	npc->y += npc->ym;
}

void Npc114_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[3] = {
		{ 0, 0, 16, 24},
		{16, 0, 32, 24},
		{32, 0, 48, 24},
	};
	
	LoadTLUT_CI4(npc_press_tlut);
	LoadTex_CI4(48, 24, npc_press_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 115 - Ravil
#include "data/bitmap/npc_ravil.inc.c"

void Npc115_Act(NPCHAR *npc)
{
	s32 i;
	
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->xm = 0;
			npc->act_no = 1;
			npc->act_wait = 0;
			npc->count1 = 0;
			//Fallthrough
		case 1:
			if (gMC.x < npc->x + (96 * 0x200) && gMC.x > npc->x - (96 * 0x200) && gMC.y < npc->y + (32 * 0x200) && gMC.y > npc->y - (96 * 0x200))
				npc->act_no = 10;
			if (npc->shock)
				npc->act_no = 10;
			break;
			
		case 10:
			if (gMC.x < npc->x)
				npc->direct = 0;
			else
				npc->direct = 2;
			
			npc->ani_no = 1;
			
			if (++npc->act_wait > 20)
			{
				npc->act_wait = 0;
				npc->act_no = 20;
			}
			break;
			
		case 20:
			npc->damage = 0;
			npc->xm = 0;
			
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			
			if (npc->ani_no > 2)
			{
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
				
				if (npc->direct == 0)
					npc->xm = -0x200;
				else
					npc->xm = 0x200;
				
				if (++npc->count1 > 2)
				{
					npc->count1 = 0;
					npc->ani_no = 4;
					npc->act_no = 21;
					npc->ym = -0x400;
					npc->xm *= 2;
					npc->damage = 5;
					PlaySoundObject(102, 1);
				}
				else
				{
					npc->act_no = 21;
					npc->ym = -0x400;
					PlaySoundObject(30, 1);
				}
			}
			break;
			
		case 21:
			if (npc->flag & 8)
			{
				PlaySoundObject(23, 1);
				npc->act_no = 20;
				npc->ani_no = 1;
				npc->ani_wait = 0;
				npc->damage = 0;
				
				if (gMC.x > npc->x + (144 * 0x200) || gMC.x < npc->x - (144 * 0x200) || gMC.y > npc->y + (48 * 0x200) || gMC.y < npc->y - (144 * 0x200))
					npc->act_no = 0;
			}
			break;
			
		case 30:
			for (i = 0; i < 8; i++)
				SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
			npc->ani_no = 0;
			npc->act_no = 0;
			break;
			
		case 50:
			npc->act_no = 51;
			npc->ani_no = 4;
			npc->damage = 0;
			npc->ym = -0x200;
			npc->bits &= ~(NPC_SOLID_SOFT | NPC_SHOOTABLE);
			PlaySoundObject(51, 1);
			//Fallthrough
		case 51:
			if (npc->flag & 8)
			{
				PlaySoundObject(23, 1);
				npc->act_no = 52;
				npc->ani_no = 5;
				npc->xm = 0;
			}
			break;
	}
	
	//Fall and move
	if (npc->act_no > 50)
		npc->ym += 0x20;
	else
		npc->ym += 0x40;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc115_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[6] = {
		{  0, 0,  24, 24},
		{ 24, 0,  48, 24},
		{ 48, 0,  72, 24},
		{ 72, 0,  96, 24},
		{ 96, 0, 120, 24},
		{120, 0, 144, 24},
	};
	
	LoadTLUT_CI4(npc_ravil_tlut);
	LoadTex_CI4(144, 24, npc_ravil_tex + (72 * 24) * (npc->direct != 0));
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 116 - Red petals
#include "data/bitmap/npc_redpetals.inc.c"

void Npc116_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 48, 16};
	
	LoadTLUT_CI4(npc_redpetals_tlut);
	LoadTex_CI4(48, 16, npc_redpetals_tex);
	PutBitmap(&rect, x, y);
}

//NPC 119 - Table and Chair
#include "data/bitmap/npc_tablechair.inc.c"

void Npc119_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 32, 16};
	
	LoadTLUT_CI4(npc_tablechair_tlut);
	LoadTex_CI4(32, 16, npc_tablechair_tex);
	PutBitmap(&rect, x, y);
}
