//NPC 125 - Hidden item
void Npc125_Act(NPCHAR *npc)
{
	if (npc->life < 990)
	{
		SetDestroyNpChar(npc->x, npc->y, npc->view.back, 8);
		PlaySoundObject(70, 1);
		if (npc->direct == 0)
			SetNpChar(87, npc->x, npc->y, 0, 0, 2, NULL, 0);
		else
			SetNpChar(86, npc->x, npc->y, 0, 0, 2, NULL, 0);
		npc->cond = 0;
	}
}

//NPC 129 - Fireball trail
#include "data/bitmap/npc_fireball.inc.c"

void Npc129_Act(NPCHAR *npc)
{
	//Animate and move
	if (++npc->ani_wait > 1)
	{
		npc->ani_wait = 0;
		if (++npc->ani_no > 2)
			npc->cond = 0;
	}
	
	npc->y += npc->ym;
}

void Npc129_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[3] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
		{32, 0, 48, 16},
	};
	
	LoadTLUT_CI4(npc_fireball_tlut);
	LoadTex_CI4(48, 16, npc_fireball_tex + (24 * 16) * npc->direct);
	PutBitmap(&rect[npc->ani_no], x, y);
}
