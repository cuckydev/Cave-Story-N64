//NPC 234 - Picked red flowers
#include "data/bitmap/npc_pickedredflowers.inc.c"

void Npc234_Act(NPCHAR *npc)
{
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->y += 16 * 0x200;
			break;
	}
}

void Npc234_Put(NPCHAR *npc, s32 x, s32 y)
{
	static const RECT rect[] = {
		{0,  0, 48, 16},
		{0, 16, 48, 32},
	};
	
	LoadTLUT_CI4(npc_pickedredflowers_tlut);
	LoadTex_CI4(48, 32, npc_pickedredflowers_tex);
	PutBitmap(&rect[npc->direct != 0], x, y);
}
