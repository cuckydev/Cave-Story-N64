//NPC 192 - Hoverbike
#include "data/bitmap/npc_hoverbike.inc.c"

void Npc192_Act(NPCHAR *npc)
{
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->view.back = 16 * 0x200;
			npc->view.front = 16 * 0x200;
			npc->view.top = 8 * 0x200;
			npc->view.bottom = 8 * 0x200;
			break;
			
		case 10:
			npc->act_no = 11;
			npc->ani_no = 1;
			npc->view.top = 16 * 0x200;
			npc->view.bottom = 16 * 0x200;
			npc->y -= 5 * 0x200;
			break;
			
		case 20:
			npc->act_no = 21;
			npc->act_wait = 1;
			npc->tgt_x = npc->x;
			npc->tgt_y = npc->y;
			//Fallthrough
		case 21:
			npc->x = npc->tgt_x + (Random(-1, 1) * 0x200);
			npc->y = npc->tgt_y + (Random(-1, 1) * 0x200);
			
			if (++npc->act_wait > 30)
				npc->act_no = 30;
			break;
			
		case 30:
			npc->act_no = 31;
			npc->act_wait = 1;
			npc->xm = -0x800;
			npc->x = npc->tgt_x;
			npc->y = npc->tgt_y;
			PlaySoundObject(44, 1);
			//Fallthrough
		case 31:
			npc->xm += 0x20;
			npc->x += npc->xm;
			npc->act_wait++;
			npc->y = npc->tgt_y + (Random(-1, 1) * 0x200);
			
			if (npc->act_wait > 10)
				npc->direct = 2;
			
			if (npc->act_wait > 200)
				npc->act_no = 40;
			break;
			
		case 40:
			npc->act_no = 41;
			npc->act_wait = 2;
			npc->direct = 0;
			npc->y -= 48 * 0x200;
			npc->xm = -0x1000;
			//Fallthrough
		case 41:
			npc->x += npc->xm;
			npc->y += npc->ym;
			
			npc->act_wait += 2;
			if (npc->act_wait > 1200)
				npc->cond = 0;
			break;
	}
	
	//Exhaust
	if (npc->act_wait % 4 == 0 && npc->act_no >= 20)
	{
		PlaySoundObject(34, 1);
		
		if (npc->direct == 0)
			SetCaret(npc->x + (10 * 0x200), npc->y + (10 * 0x200), 7, 2);
		else
			SetCaret(npc->x - (10 * 0x200), npc->y + (10 * 0x200), 7, 0);
	}
}

void Npc192_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[2][2] = {
		{
			{ 0, 0, 32, 16},
			{32, 0, 64, 32},
		},
		{
			{ 0, 16, 32, 32},
			{64,  0, 96, 32},
		}
	};
	
	LoadTLUT_CI4(npc_hoverbike_tlut);
	LoadTex_CI4(96, 32, npc_hoverbike_tex);
	PutBitmap(&rect[npc->direct != 0][npc->ani_no], x, y);
}

//NPC 193 - Broken skooter
void Npc193_Act(NPCHAR *npc)
{
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->x += 24 * 0x200;
			break;
	}
}

void Npc193_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect = {32, 0, 96, 16};
	LoadTLUT_CI4(npc_hoverbike_tlut);
	LoadTex_CI4(96, 16, npc_hoverbike_tex + (48 * 32));
	PutBitmap(&rect, x, y);
}

//NPC 199 - Fan wind
void Npc199_Act(NPCHAR *npc)
{
	//Move in facing direction
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = Random(0, 2);
			
			switch (npc->direct)
			{
				case 0:
					npc->xm = -1;
					break;
				case 1:
					npc->ym = -1;
					break;
				case 2:
					npc->xm = 1;
					break;
				case 3:
					npc->ym = 1;
					break;
			}
			
			npc->xm *= (Random(4, 8) * 0x200) / 2;
			npc->ym *= (Random(4, 8) * 0x200) / 2;
			break;
	}
	
	//Animate
	if (++npc->ani_wait > 6)
	{
		npc->ani_wait = 0;
		npc->ani_no++;
	}
	if (npc->ani_no > 4)
		npc->cond = 0;
	
	//Move
	npc->x += npc->xm;
	npc->y += npc->ym;
}

void Npc199_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{0, 0,  2, 2},
		{2, 0,  4, 2},
		{4, 0,  6, 2},
		{6, 0,  8, 2},
		{8, 0, 10, 2},
	};
	
	LoadTLUT_CI4(npc_waterdrop_tlut);
	LoadTex_CI4(16, 4, npc_waterdrop_tex);
	PutBitmap(&rect[npc->ani_no], x, y);
}
