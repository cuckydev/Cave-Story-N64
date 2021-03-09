//NPC 020 - Computer
#include "data/bitmap/npc_computer.inc.c"

void Npc020_Act(NPCHAR *npc)
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

void Npc020_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][3] = {
		{
			{0,  0, 32, 24},
			{0,  0, 32, 24},
			{0,  0, 32, 24},
		},
		{
			{0, 24, 32, 48},
			{0, 24, 32, 48},
			{0, 48, 32, 72},
		},
	};
	
	LoadTLUT_CI4(npc_computer_tlut);
	LoadTex_CI4(32, 72, npc_computer_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//NPC 021 - Open Chest
void Npc021_Act(NPCHAR *npc)
{
	if (npc->act_no == 0)
	{
		npc->act_no = 1;
		if (npc->direct == 2)
			npc->y += 16 * 0x200;
	}
}

void Npc021_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {48, 8, 64, 16};
	
	LoadTLUT_CI4(npc_chest_tlut);
	LoadTex_CI4(64, 16, npc_chest_tex);
	PutBitmap(&rect, x, y);
}

//NPC 022 - Teleporter
#include "data/bitmap/npc_teleporter.inc.c"

void Npc022_Act(NPCHAR *npc)
{
	//Animate
	switch (npc->act_no)
	{
		case 0:
			npc->ani_no = 0;
			break;
		case 1:
			if (++npc->ani_no > 1)
				npc->ani_no = 0;
			break;
	}
}

void Npc022_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0,  0, 24, 32},
		{ 0, 32, 24, 64},
	};
	
	LoadTLUT_CI4(npc_teleporter_tlut);
	LoadTex_CI4(48, 64, npc_teleporter_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 023 - Teleporter Lights
void Npc023_Act(NPCHAR *npc)
{
	//Animate
	if (++npc->ani_wait > 1)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 7)
		npc->ani_no = 0;
}

void Npc023_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{24,  0, 48,  4},
		{24,  4, 48,  8},
		{24,  8, 48, 12},
		{24, 12, 48, 16},
		{24, 16, 48, 20},
		{24, 20, 48, 24},
		{24, 24, 48, 28},
		{24, 28, 48, 32},
	};
	
	LoadTLUT_CI4(npc_teleporter_tlut);
	LoadTex_CI4(48, 64, npc_teleporter_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 024 - Power Critter
#include "data/bitmap/npc_powercritter.inc.c"

void Npc024_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->y += 3 * 0x200;
			npc->act_no = 1;
			//Fallthrough
		case 1:
			if (npc->act_wait >= 8 && npc->x - (128 * 0x200) < gMC.x && npc->x + (128 * 0x200) > gMC.x && npc->y - (128 * 0x200) < gMC.y && npc->y + (48 * 0x200) > gMC.y)
			{
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
				npc->ani_no = 1;
			}
			else
			{
				if (npc->act_wait < 8)
					npc->act_wait++;
				npc->ani_no = 0;
			}
			
			if (npc->shock)
			{
				npc->act_no = 2;
				npc->ani_no = 0;
				npc->act_wait = 0;
			}
			
			if (npc->act_wait >= 8 && npc->x - (96 * 0x200) < gMC.x && npc->x + (96 * 0x200) > gMC.x && npc->y - (96 * 0x200) < gMC.y && npc->y + (48 * 0x200) > gMC.y)
			{
				npc->act_no = 2;
				npc->ani_no = 0;
				npc->act_wait = 0;
			}
			break;
			
		case 2:
			if (++npc->act_wait > 8)
			{
				npc->act_no = 3;
				npc->ani_no = 2;
				npc->ym = -0x5FF;
				PlaySoundObject(108, 1);
				
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
				
				if (npc->direct == 0)
					npc->xm = -0x100;
				else
					npc->xm = 0x100;
			}
			break;
			
		case 3:
			if (npc->ym > 0x200)
			{
				npc->tgt_y = npc->y;
				npc->act_no = 4;
				npc->ani_no = 3;
				npc->act_wait = 0;
				npc->act_wait = 0;
			}
			break;
			
		case 4:
			if (npc->x < gMC.x)
				npc->direct = 2;
			else
				npc->direct = 0;
			
			npc->act_wait++;
			
			if (npc->flag & 7 || npc->act_wait > 100)
			{
				npc->damage = 12;
				npc->act_no = 5;
				npc->ani_no = 2;
				npc->xm /= 2;
				break;
			}
			
			if (npc->act_wait % 4 == 1)
				PlaySoundObject(110, 1);
			
			if (++npc->ani_wait > 0)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			
			if (npc->ani_no > 5)
				npc->ani_no = 3;
			break;
			
		case 5:
			if (npc->flag & 8)
			{
				npc->damage = 2;
				npc->xm = 0;
				npc->act_wait = 0;
				npc->ani_no = 0;
				npc->act_no = 1;
				PlaySoundObject(26, 1);
				SetQuake(30);
			}
			break;
	}
	
	//Gravity
	if (npc->act_no != 4)
	{
		npc->ym += 0x20;
		if (npc->ym > 0x5FF)
			npc->ym = 0x5FF;
	}
	else
	{
		if (npc->x < gMC.x)
			npc->xm += 0x20;
		else
			npc->xm -= 0x20;
		
		if (npc->y > npc->tgt_y)
			npc->ym -= 0x10;
		else
			npc->ym += 0x10;
		
		if (npc->ym > 0x200)
			npc->ym = 0x200;
		if (npc->ym < -0x200)
			npc->ym = -0x200;
		
		if (npc->xm > 0x200)
			npc->xm = 0x200;
		if (npc->xm < -0x200)
			npc->xm = -0x200;
	}
	
	//Move
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc024_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[6] = {
		{0, 0, 24, 24},
		{24, 0, 48, 24},
		{48, 0, 72, 24},
		{72, 0, 96, 24},
		{96, 0, 120, 24},
		{120, 0, 144, 24},
	};
	
	LoadTLUT_CI4(npc_powercritter_tlut);
	LoadTex_CI4(144, 24, npc_powercritter_tex + (72 * 24) * (npc->direct != 0));
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 025 - Egg Corridor lift
#include "data/bitmap/npc_lift.inc.c"

void Npc025_Act(NPCHAR *npc)
{
	//Move
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			npc->x += 8 * 0x200;
			// Fallthrough
		case 1:
			if (++npc->act_wait > 150)
			{
				npc->act_wait = 0;
				npc->act_no++;
			}
			break;
			
		case 2:
			if (++npc->act_wait <= 0x40)
			{
				npc->y -= 1 * 0x200;
			}
			else
			{
				npc->act_wait = 0;
				npc->act_no++;
			}
			break;
			
		case 3:
			if (++npc->act_wait > 150)
			{
				npc->act_wait = 0;
				npc->act_no++;
			}
			break;
			
		case 4:
			if (++npc->act_wait <= 0x40)
			{
				npc->y -= 1 * 0x200;
			}
			else
			{
				npc->act_wait = 0;
				npc->act_no++;
			}
			break;
			
		case 5:
			if (++npc->act_wait > 150)
			{
				npc->act_wait = 0;
				npc->act_no++;
			}
			break;
			
		case 6:
			if (++npc->act_wait <= 0x40)
			{
				npc->y += 1 * 0x200;
			}
			else
			{
				npc->act_wait = 0;
				npc->act_no++;
			}
			break;
			
		case 7:
			if (++npc->act_wait > 150)
			{
				npc->act_wait = 0;
				npc->act_no++;
			}
			break;
			
		case 8:
			if (++npc->act_wait <= 0x40)
			{
				npc->y += 1 * 0x200;
			}
			else
			{
				npc->act_wait = 0;
				npc->act_no = 1;
			}
			break;
	}
	
	//Animate
	switch (npc->act_no)
	{
		case 2:
		case 4:
		case 6:
		case 8:
			if (++npc->ani_wait > 1)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 1)
				npc->ani_no = 0;
			break;
	}
}

void Npc025_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{0,  0, 32, 16},
		{0, 16, 32, 32},
	};
	
	LoadTLUT_CI4(npc_lift_tlut);
	LoadTex_CI4(32, 32, npc_lift_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 026 - Grasstown Bat (Flying)
#include "data/bitmap/npc_bat.inc.c"

void Npc026_Act(NPCHAR *npc)
{
	//Handle flying
	u8 deg;
	
	switch (npc->act_no)
	{
		case 0:
			deg = Random(0, 0xFF);
			npc->xm = GetCos(deg);
			deg += 0x40;
			npc->tgt_x = npc->x + (GetCos(deg) * 8);
			
			deg = Random(0, 0xFF);
			npc->ym = GetSin(deg);
			deg += 0x40;
			npc->tgt_y = npc->y + (GetSin(deg) * 8);
			
			npc->act_no = 1;
			npc->count1 = 120;
			//Fallthrough
		case 1:
			if (gMC.x < npc->x)
				npc->direct = 0;
			else
				npc->direct = 2;
			
			if (npc->tgt_x < npc->x)
				npc->xm -= 0x10;
			if (npc->tgt_x > npc->x)
				npc->xm += 0x10;
			
			if (npc->tgt_y < npc->y)
				npc->ym -= 0x10;
			if (npc->tgt_y > npc->y)
				npc->ym += 0x10;
			
			if (npc->xm > 0x200)
				npc->xm = 0x200;
			if (npc->xm < -0x200)
				npc->xm = -0x200;
			
			if (npc->ym > 0x200)
				npc->ym = 0x200;
			if (npc->ym < -0x200)
				npc->ym = -0x200;
			
			if (npc->count1 < 120)
			{
				npc->count1++;
				break;
			}
			
			if (npc->x - (8 * 0x200) < gMC.x && npc->x + (8 * 0x200) > gMC.x && npc->y < gMC.y && npc->y + (96 * 0x200) > gMC.y)
			{
				npc->xm /= 2;
				npc->ym = 0;
				npc->act_no = 3;
				npc->bits &= ~NPC_IGNORE_SOLIDITY;
			}
			break;
			
		case 3:
			npc->ym += 0x40;
			if (npc->ym > 0x5FF)
				npc->ym = 0x5FF;
			
			if (npc->flag & 8)
			{
				npc->ym = 0;
				npc->xm *= 2;
				npc->count1 = 0;
				npc->act_no = 1;
				npc->bits |= NPC_IGNORE_SOLIDITY;
			}
			break;
	}
	
	//Move
	npc->x += npc->xm;
	npc->y += npc->ym;
	
	//Animate
	if (npc->act_no == 3)
	{
		npc->ani_no = 3;
	}
	else
	{
		if (++npc->ani_wait > 1)
		{
			npc->ani_wait = 0;
			npc->ani_no++;
		}
		if (npc->ani_no > 2)
			npc->ani_no = 0;
	}
}

void Npc026_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][4] = {
		{
			{32, 0, 48, 16},
			{48, 0, 64, 16},
			{64, 0, 80, 16},
			{80, 0, 96, 16},
		},
		{
			{32, 16, 48, 32},
			{48, 16, 64, 32},
			{64, 16, 80, 32},
			{80, 16, 96, 32},
		},
	};
	
	LoadTLUT_CI4(npc_bat_weed_tlut);
	LoadTex_CI4(96, 32, npc_bat_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//NPC 027 - Death trap
#include "data/bitmap/npc_deathtrap.inc.c"

void Npc027_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 32, 24};
	LoadTLUT_CI4(npc_deathtrap_tlut);
	LoadTex_CI4(32, 24, npc_deathtrap_tex);
	PutBitmap(&rect, x, y);
}

//NPC 028 - Grasstown Critter
void Npc028_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->y += 3 * 0x200;
			npc->act_no = 1;
			//Fallthrough
		case 1:
			if (npc->act_wait >= 8 && npc->x - (128 * 0x200) < gMC.x && npc->x + (128 * 0x200) > gMC.x && npc->y - (128 * 0x200) < gMC.y && npc->y + (48 * 0x200) > gMC.y)
			{
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
				npc->ani_no = 1;
			}
			else
			{
				if (npc->act_wait < 8)
					npc->act_wait++;
				npc->ani_no = 0;
			}
			
			if (npc->shock)
			{
				npc->act_no = 2;
				npc->ani_no = 0;
				npc->act_wait = 0;
			}
			
			if (npc->act_wait >= 8 && npc->x - (96 * 0x200) < gMC.x && npc->x + (96 * 0x200) > gMC.x && npc->y - (96 * 0x200) < gMC.y && npc->y + (48 * 0x200) > gMC.y)
			{
				npc->act_no = 2;
				npc->ani_no = 0;
				npc->act_wait = 0;
			}
			break;
			
		case 2:
			if (++npc->act_wait > 8)
			{
				npc->act_no = 3;
				npc->ani_no = 2;
				npc->ym = -0x4CC;
				PlaySoundObject(30, 1);
				
				if (npc->x > gMC.x)
					npc->direct = 0;
				else
					npc->direct = 2;
				
				if (npc->direct == 0)
					npc->xm = -0x100;
				else
					npc->xm = 0x100;
			}
			break;
			
		case 3:
			if (npc->ym > 0x100)
			{
				npc->tgt_y = npc->y;
				npc->act_no = 4;
				npc->ani_no = 3;
				npc->act_wait = 0;
				npc->act_wait = 0;
			}
			break;
			
		case 4:
			if (npc->x < gMC.x)
				npc->direct = 2;
			else
				npc->direct = 0;
			
			npc->act_wait++;
			
			if (npc->flag & 7 || npc->act_wait > 100)
			{
				npc->damage = 3;
				npc->act_no = 5;
				npc->ani_no = 2;
				npc->xm /= 2;
				break;
			}
			
			if (npc->act_wait % 4 == 1)
				PlaySoundObject(109, 1);
			
			if (npc->flag & 8)
				npc->ym = -0x200;
			
			if (++npc->ani_wait > 0)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 5)
				npc->ani_no = 3;
			break;
			
		case 5:
			if (npc->flag & 8)
			{
				npc->damage = 2;
				npc->xm = 0;
				npc->act_wait = 0;
				npc->ani_no = 0;
				npc->act_no = 1;
				PlaySoundObject(23, 1);
			}
			break;
	}
	
	//Gravity
	if (npc->act_no != 4)
	{
		npc->ym += 0x40;
		if (npc->ym > 0x5FF)
			npc->ym = 0x5FF;
	}
	else
	{
		if (npc->x < gMC.x)
			npc->xm += 0x20;
		else
			npc->xm -= 0x20;
		
		if (npc->y > npc->tgt_y)
			npc->ym -= 0x10;
		else
			npc->ym += 0x10;
		
		if (npc->ym > 0x200)
			npc->ym = 0x200;
		if (npc->ym < -0x200)
			npc->ym = -0x200;
		
		if (npc->xm > 0x200)
			npc->xm = 0x200;
		if (npc->xm < -0x200)
			npc->xm = -0x200;
	}
	
	//Move
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc028_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][6] = {
		{
			{0,  0, 16, 16},
			{16, 0, 32, 16},
			{32, 0, 48, 16},
			{48, 0, 64, 16},
			{64, 0, 80, 16},
			{80, 0, 96, 16},
		},
		{
			{0,  16, 16, 32},
			{16, 16, 32, 32},
			{32, 16, 48, 32},
			{48, 16, 64, 32},
			{64, 16, 80, 32},
			{80, 16, 96, 32},
		},
	};
	
	LoadTLUT_CI4(npc_critter_weed_tlut);
	LoadTex_CI4(96, 32, npc_critter_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//NPC 029 - Cthulhu
#include "data/bitmap/npc_cthulhu.inc.c"

void Npc029_Act(NPCHAR *npc)
{
	//Animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			//Fallthrough
		case 1:
			if (npc->x - (48 * 0x200) < gMC.x && npc->x + (48 * 0x200) > gMC.x && npc->y - (48 * 0x200) < gMC.y && npc->y + (16 * 0x200) > gMC.y)
				npc->ani_no = 1;
			else
				npc->ani_no = 0;
			break;
	}
}

void Npc029_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][2] = {
		{
			{ 0, 0, 16, 24},
			{16, 0, 32, 24},
		},
		{
			{ 0, 24, 16, 48},
			{16, 24, 32, 48},
		}
	};
	
	LoadTLUT_CI4(npc_cthulhu_tlut);
	LoadTex_CI4(32, 48, npc_cthulhu_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//NPC 030 - Gunsmith
#include "data/bitmap/npc_gunsmith.inc.c"

void Npc030_Act(NPCHAR *npc)
{
	//Do stuff
	if (npc->direct == 0)
	{
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
				break;
				
			case 2:
				if (++npc->act_wait > 8)
				{
					npc->act_no = 1;
					npc->ani_no = 0;
				}
				break;
		}
	}
	else
	{
		if (npc->act_no == 0)
		{
			npc->act_no = 1;
			npc->y += 16 * 0x200;
			npc->ani_no = 2;
		}
		
		if (++npc->act_wait > 100)
		{
			npc->act_wait = 0;
			SetCaret(npc->x, npc->y - (2 * 0x200), 5, 0);
		}
	}
}

void Npc030_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
		{32, 0, 48, 16},
	};
	
	LoadTLUT_CI4(npc_gunsmith_tlut);
	LoadTex_CI4(48, 16, npc_gunsmith_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 031 - Grasstown Bat (Hanging)
void Npc031_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			//Fallthrough
		case 1:
			if (Random(0, 120) == 10)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 1;
			}
			
			if (npc->x - (8 * 0x200) < gMC.x && npc->x + (8 * 0x200) > gMC.x && npc->y - (8 * 0x200) < gMC.y && npc->y + (96 * 0x200) > gMC.y)
			{
				npc->ani_no = 0;
				npc->act_no = 3;
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
			npc->ani_no = 0;
			
			if (npc->shock || npc->x - (20 * 0x200) > gMC.x || npc->x + (20 * 0x200) < gMC.x)
			{
				npc->ani_no = 1;
				npc->ani_wait = 0;
				npc->act_no = 4;
				npc->act_wait = 0;
			}
			break;
			
		case 4:
			npc->ym += 0x20;
			if (npc->ym > 0x5FF)
				npc->ym = 0x5FF;
			
			if (++npc->act_wait < 20 && !(npc->flag & 8))
				break;
			
			if (npc->flag & 8 || npc->y > gMC.y - (16 * 0x200))
			{
				npc->ani_wait = 0;
				npc->ani_no = 2;
				npc->act_no = 5;
				npc->tgt_y = npc->y;
				
				if (npc->flag & 8)
					npc->ym = -0x200;
			}
			break;
			
		case 5:
			if (++npc->ani_wait > 1)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			
			if (npc->ani_no > 4)
				npc->ani_no = 2;
			
			if (gMC.x < npc->x)
				npc->direct = 0;
			else
				npc->direct = 2;
			
			if (gMC.x < npc->x)
				npc->xm -= 0x10;
			if (gMC.x > npc->x)
				npc->xm += 0x10;
			
			if (npc->tgt_y < npc->y)
				npc->ym -= 0x10;
			if (npc->tgt_y > npc->y)
				npc->ym += 0x10;
			
			if (npc->xm > 0x200)
				npc->xm = 0x200;
			if (npc->xm < -0x200)
				npc->xm = -0x200;
			
			if (npc->ym > 0x200)
				npc->ym = 0x200;
			if (npc->ym < -0x200)
				npc->ym = -0x200;
			
			if (npc->flag & 8)
				npc->ym = -0x200;
			if (npc->flag & 2)
				npc->ym = 0x200;
			break;
	}
	
	//Move
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc031_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][5] = {
		{
			{0,  0, 16, 16},
			{16, 0, 32, 16},
			{32, 0, 48, 16},
			{48, 0, 64, 16},
			{64, 0, 80, 16},
		},
		{
			{0,  16, 16, 32},
			{16, 16, 32, 32},
			{32, 16, 48, 32},
			{48, 16, 64, 32},
			{64, 16, 80, 32},
		},
	};
	
	LoadTLUT_CI4(npc_bat_weed_tlut);
	LoadTex_CI4(96, 32, npc_bat_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//NPC 032 - Life Capsule
#include "data/bitmap/npc_lifecapsule.inc.c"

void Npc032_Act(NPCHAR *npc)
{
	//Animate
	if (++npc->ani_wait > 2)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 1)
		npc->ani_no = 0;
}

void Npc032_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
	};
	
	LoadTLUT_CI4(npc_lifecapsule_tlut);
	LoadTex_CI4(32, 16, npc_lifecapsule_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 033 - Balrog bouncing projectile
#include "data/bitmap/npc_balrogprojectile.inc.c"

void Npc033_Act(NPCHAR *npc)
{
	//Move
	if (npc->flag & 5)
	{
		SetCaret(npc->x, npc->y, 2, 0);
		npc->cond = 0;
	}
	else if (npc->flag & 8)
	{
		npc->ym = -0x400;
	}
	
	npc->ym += 0x2A;
	npc->y += npc->ym;
	npc->x += npc->xm;
	
	//Animate
	if (++npc->ani_wait > 2)
	{
		npc->ani_wait = 0;
		if (++npc->ani_no > 1)
			npc->ani_no = 0;
	}
	
	//Delete after 250 frames
	if (++npc->act_wait > 250)
	{
		SetCaret(npc->x, npc->y, 2, 0);
		npc->cond = 0;
	}
}

void Npc033_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2] = {
		{0,  0, 16, 16},
		{0, 16, 16, 32},
	};
	
	LoadTLUT_CI4(npc_balrogprojectile_tlut);
	LoadTex_CI4(16, 32, npc_balrogprojectile_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 034 - Bed
#include "data/bitmap/npc_bed.inc.c"

void Npc034_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 32, 16},
		{32, 0, 64, 16},
	};
	
	LoadTLUT_CI4(npc_bed_tlut);
	LoadTex_CI4(64, 16, npc_bed_tex);
	PutBitmap(&rect[npc->direct != 0], x, y);
}

//NPC 035 - Mannan
#include "data/bitmap/npc_mannan.inc.c"

void Npc035_Act(NPCHAR *npc)
{
	//React to being shot
	if (npc->act_no < 3 && npc->life < 90)
	{
		PlaySoundObject(71, 1);
		SetDestroyNpChar(npc->x, npc->y, npc->view.back, 8);
		SetExpObjects(npc->x, npc->y, npc->exp);
		npc->act_no = 3;
		npc->act_wait = 0;
		npc->ani_no = 2;
		npc->bits &= ~NPC_SHOOTABLE;
		npc->damage = 0;
	}
	
	//Animate
	switch (npc->act_no)
	{
		case 0:
		case 1:
			if (npc->shock)
			{
				if (npc->direct == 0)
					SetNpChar(103, npc->x - (8 * 0x200), npc->y + (8 * 0x200), 0, 0, npc->direct, NULL, 0x100);
				else
					SetNpChar(103, npc->x + (8 * 0x200), npc->y + (8 * 0x200), 0, 0, npc->direct, NULL, 0x100);
				
				npc->ani_no = 1;
				npc->act_no = 2;
				npc->act_wait = 0;
			}
			break;
			
		case 2:
			if (++npc->act_wait > 20)
			{
				npc->act_wait = 0;
				npc->act_no = 1;
				npc->ani_no = 0;
			}
			break;
			
		case 3:
			if (++npc->act_wait == 50 || npc->act_wait == 60)
				npc->ani_no = 3;
			if (npc->act_wait == 53 || npc->act_wait == 63)
				npc->ani_no = 2;
			if (npc->act_wait > 100)
				npc->act_no = 4;
			break;
	}
}

void Npc035_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 24, 32},
		{24, 0, 48, 32},
		{48, 0, 72, 32},
		{72, 0, 96, 32},
	};
	
	LoadTLUT_CI4(npc_mannan_tlut);
	LoadTex_CI4(96, 32, npc_mannan_tex + (48 * 32) * (npc->direct != 0));
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 036 - Balrog (Hover)
void Npc036_Act(NPCHAR *npc)
{
	s32 i;
	u8 deg;
	s32 xm, ym;
	
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			//Fallthrough
		case 1:
			if (++npc->act_wait > 12)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->count1 = 3;
				npc->ani_no = 1;
			}
			break;
			
		case 2:
			if (++npc->act_wait > 16)
			{
				npc->count1--;
				npc->act_wait = 0;
				
				deg = GetArktan(npc->x - gMC.x, npc->y + (4 * 0x200) - gMC.y);
				deg += (u8)Random(-0x10, 0x10);
				ym = GetSin(deg);
				xm = GetCos(deg);
				
				SetNpChar(11, npc->x, npc->y + 0x800, xm, ym, 0, NULL, 0x100);
				PlaySoundObject(39, 1);
				
				if (npc->count1 == 0)
				{
					npc->act_no = 3;
					npc->act_wait = 0;
				}
			}
			break;
			
		case 3:
			if (++npc->act_wait > 3)
			{
				npc->act_no = 4;
				npc->act_wait = 0;
				npc->xm = (gMC.x - npc->x) / 100;
				npc->ym = -0x600;
				npc->ani_no = 3;
			}
			break;
			
		case 4:
			if (npc->ym > -0x200)
			{
				if (npc->life > 60)
				{
					npc->act_no = 5;
					npc->ani_no = 4;
					npc->ani_wait = 0;
					npc->act_wait = 0;
					npc->tgt_y = npc->y;
				}
				else
				{
					npc->act_no = 6;
				}
			}
			break;
			
		case 5:
			if (++npc->ani_wait > 1)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 5)
			{
				npc->ani_no = 4;
				PlaySoundObject(47, 1);
			}
			
			if (++npc->act_wait > 100)
			{
				npc->act_no = 6;
				npc->ani_no = 3;
			}
			
			if (npc->y < npc->tgt_y)
				npc->ym += 0x40;
			else
				npc->ym -= 0x40;
			
			if (npc->ym < -0x200)
				npc->ym = -0x200;
			if (npc->ym > 0x200)
				npc->ym = 0x200;
			break;
			
		case 6:
			if (npc->y + (16 * 0x200) < gMC.y)
				npc->damage = 10;
			else
				npc->damage = 0;
			
			if (npc->flag & 8)
			{
				npc->act_no = 7;
				npc->act_wait = 0;
				npc->ani_no = 2;
				PlaySoundObject(26, 1);
				PlaySoundObject(25, 1);
				SetQuake(30);
				npc->damage = 0;
				
				for (i = 0; i < 8; ++i)
					SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, NULL, 0x100);
				for (i = 0; i < 8; ++i)
					SetNpChar(33, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-0x400, 0x400), Random(-0x400, 0), 0, NULL, 0x100);
			}
			break;
			
		case 7:
			npc->xm = 0;
			
			if (++npc->act_wait > 3)
			{
				npc->act_no = 1;
				npc->act_wait = 0;
			}
			break;
	}
	
	//Gravity and face player
	if (npc->act_no != 5)
	{
		npc->ym += 0x33;
		if (npc->x < gMC.x)
			npc->direct = 2;
		else
			npc->direct = 0;
	}
	
	//Limit speed
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	
	//Move
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc036_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const s32 frame[] = {
		0/40,
		40/40,
		80/40,
		120/40,
		8+160/40,
		8+200/40,
	};
	static const RECT rect[2] = {
		{ 0, 0, 40, 24},
		{40, 0, 80, 24},
	};
	
	LoadTLUT_CI4(npc_balrog_tlut);
	LoadTex_CI4(80, 24, npc_balrog_tex + (40 * 24) * frame[npc->ani_no]);
	PutBitmap(&rect[npc->direct != 0], x, y);
}

//NPC 037 - Save sign
#include "data/bitmap/npc_sign.inc.c"

void Npc037_Act(NPCHAR *npc)
{
	//Animate
	if (++npc->ani_wait > 1)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 1)
		npc->ani_no = 0;
}

void Npc037_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
	};
	
	LoadTLUT_CI4(npc_sign_tlut);
	LoadTex_CI4(32, 16, npc_sign_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 038 - Fire
#include "data/bitmap/npc_fire.inc.c"

void Npc038_Act(NPCHAR *npc)
{
	//Animate
	switch (npc->act_no)
	{
		case 0:
			if (++npc->ani_wait > 3)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 3)
				npc->ani_no = 0;
			break;
			
		case 10:
			npc->act_no = 11;
			SetDestroyNpChar(npc->x, npc->y, npc->view.back, 8);
			//Fallthrough
		case 11:
			break;
	}
}

void Npc038_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
		{32, 0, 48, 16},
		{48, 0, 64, 16},
	};
	
	if (npc->act_no != 11)
	{
		LoadTLUT_CI4(npc_fire_tlut);
		LoadTex_CI4(64, 16, npc_fire_tex);
		PutBitmap(&rect[npc->ani_no], x, y);
	}
}

//NPC 039 - Save sign
#include "data/bitmap/npc_savesign.inc.c"

void Npc039_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
	};
	
	LoadTLUT_CI4(npc_savesign_tlut);
	LoadTex_CI4(32, 16, npc_savesign_tex);
	PutBitmap(&rect[npc->direct != 0], x, y);
}
