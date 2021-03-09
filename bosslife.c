#include "bosslife.h"
#include "npchar.h"
#include "draw.h"

//Boss life structure
BOSSLIFE gBL;

//Boss life functions
void InitBossLife()
{
	gBL.flag = FALSE;
}

BOOL StartBossLife(s32 code_event)
{
	s32 i = 0;
	while (i < NPC_MAX && gNPC[i].code_event != code_event)
		i++;
	
	if (i == NPC_MAX)
		return FALSE;
	
	gBL.flag = TRUE;
	gBL.id = gNPC[i].code_char;
	gBL.pId = &gNPC[i].code_char;
	gBL.max = gNPC[i].life;
	gBL.br = gNPC[i].life;
	gBL.pLife = &gNPC[i].life;
	return TRUE;
}

BOOL StartBossLife2()
{
	//gBL.flag = TRUE;
	//gBL.pId = NULL;
	//gBL.max = gBoss[0].life;
	//gBL.br = gBoss[0].life;
	//gBL.pLife = &gBoss[0].life;
	return TRUE;
}

#include "data/bitmap/textbox.inc.c"
#include "data/bitmap/bosslife.inc.c"
#include "data/bitmap/bosslifebar.inc.c"

void PutBossLife()
{
	static const RECT rcBox1 = {0, 0, 256, 8};
	static const RECT rcBox2 = {0, 8, 256, 16};
	static const RECT rcText = {0, 0, 32, 8};
	RECT rcLife = {0, 0, 0, 8};
	RECT rcBr = {0, 8, 0, 16};
	
	if (gBL.flag == FALSE)
		return;
	
	if (*gBL.pLife <= 0)
	{
		gBL.flag = FALSE;
		return;
	}
	
	if (gBL.pId != NULL && *gBL.pId != gBL.id)
	{
		gBL.flag = FALSE;
		return;
	}
	
	rcLife.right = (*gBL.pLife * 198) / gBL.max;
	
	if (gBL.br > *gBL.pLife)
	{
		if (++gBL.count > 30)
			gBL.br--;
	}
	else
	{
		gBL.count = 0;
	}
	
	rcBr.right = (gBL.br * 198) / gBL.max;
	
	//Draw frame
	LoadTLUT_CI4(textbox_tlut);
	
	LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 0);
	PutBitmap(&rcBox1, (SCREEN_WIDTH - 256) / 2 - 6, SCREEN_HEIGHT - 20);
	
	LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 2);
	PutBitmap(&rcBox2, (SCREEN_WIDTH - 256) / 2 - 6, SCREEN_HEIGHT - 12);
	
	//Draw bar
	LoadTLUT_CI4(bosslifebar_tlut);
	LoadTex_CI4(240, 16, bosslifebar_tex);
	PutBitmap(&rcBr,   (SCREEN_WIDTH / 2) - 88, SCREEN_HEIGHT - 16);
	PutBitmap(&rcLife, (SCREEN_WIDTH / 2) - 88, SCREEN_HEIGHT - 16);
	
	//Draw 'Boss <3' label
	LoadTLUT_CI4(bosslife_tlut);
	LoadTex_CI4(32, 8, bosslife_tex);
	PutBitmap(&rcText, (SCREEN_WIDTH / 2) - 120, SCREEN_HEIGHT - 16);
}
