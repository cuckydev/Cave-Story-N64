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

//NPC 029 - Cthulhu
//Cthulhu
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
