//NPC 298 - Opening Doctor
#include "data/bitmap/npc_openingdoctor.inc.c"

void Npc298_Act(NPCHAR *npc)
{
	//Move and animate
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->y -= 8 * 0x200;
			//Fallthrough
		case 1:
			npc->ani_no = 0;
			break;
			
		case 10:
			npc->act_no = 11;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			npc->count1 = 0;
			//Fallthrough
		case 11:
			if (++npc->ani_wait > 6)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			
			if (npc->ani_no > 1)
			{
				npc->ani_no = 0;
				if (++npc->count1 > 7)
				{
					npc->ani_no = 0;
					npc->act_no = 1;
				}
			}
			break;
			
		case 20:
			npc->act_no = 21;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			//Fallthrough
		case 21:
			if (++npc->ani_wait > 10)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 5)
				npc->ani_no = 2;
			
			npc->x += 0x100;
			break;
			
		case 30:
			npc->ani_no = 6;
			break;
			
		case 40:
			npc->act_no = 41;
			npc->ani_no = 6;
			npc->ani_wait = 0;
			npc->count1 = 0;
			//Fallthrough
		case 41:
			if (++npc->ani_wait > 6)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			
			if (npc->ani_no > 7)
			{
				npc->ani_no = 6;
				if (++npc->count1 > 7)
				{
					npc->ani_no = 6;
					npc->act_no = 30;
				}
			}
			break;
	}
}

void Npc298_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{ 0, 0, 16, 32},
		{16, 0, 32, 32},
		{32, 0, 48, 32},
		{ 0, 0, 16, 32},
		{48, 0, 64, 32},
		{ 0, 0, 16, 32},
		{64, 0, 80, 32},
		{80, 0, 96, 32},
	};
	LoadTLUT_CI4(npc_openingdoctor_tlut);
	LoadTex_CI4(96, 32, npc_openingdoctor_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}

//NPC 299 - Balrog and Misery in bubbles
#include "data/bitmap/npc_kings.inc.c"

void Npc299_Act(NPCHAR *npc)
{
	//Move and animate
	if (npc->act_no == 0)
	{
		npc->act_no = 1;
		
		if (npc->direct == 0)
		{
			npc->ani_no = 1;
			npc->act_wait = 25;
			npc->y -= 0x40 * (50 / 2);
		}
		else
		{
			npc->ani_no = 0;
			npc->act_wait = 0;
		}
	}
	
	if (++npc->act_wait / 50 % 2)
		npc->y += 0x40;
	else
		npc->y -= 0x40;
}

void Npc299_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {0, 0, 48, 48};
	LoadTLUT_CI4(npc_kings_tlut);
	LoadTex_CI4(48, 48, npc_kings_tex + (24 * 48) * npc->ani_no);
	PutBitmap(&rect, x, y);
}
