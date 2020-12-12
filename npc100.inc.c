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
