#include "mycparam.h"
#include "mychar.h"
#include "game.h"
#include "draw.h"

#include "data/bitmap/healthbar.inc.c"

//Life
void AddLifeMyChar(s32 x)
{
	gMC.life += x;
	if (gMC.life > gMC.max_life)
		gMC.life = gMC.max_life;
	gMC.lifeBr = gMC.life;
}

void AddMaxLifeMyChar(s32 val)
{
	gMC.max_life += val;
	if (gMC.max_life > 232)
		gMC.max_life = 232;
	gMC.life += val;
	gMC.lifeBr = gMC.life;
}

void PutMyLife(BOOL flash)
{
	RECT rcCase = {0, 0, 232, 8};
	RECT rcLife = {0, 0, 232, 8};
	RECT rcBr = {0, 0, 232, 8};
	
	if (flash == TRUE && gMC.shock / 2 % 2)
		return;
	
	if (gMC.lifeBr < gMC.life)
		gMC.lifeBr = gMC.life;
	
	if (gMC.lifeBr > gMC.life)
	{
		if (++gMC.lifeBr_count > 30)
			--gMC.lifeBr;
	}
	else
	{
		gMC.lifeBr_count = 0;
	}
	
	//Draw bar
	rcCase.right = 64;
	rcLife.right = ((gMC.life * 40) / gMC.max_life) - 1;
	rcBr.right = ((gMC.lifeBr * 40) / gMC.max_life) - 1;
	
	LoadTLUT_CI4(healthbar_tlut);
	
	LoadTex_CI4(256, 8, healthbar_tex + (128 * 8) * 2);
	PutBitmap(&rcCase, 16, 40);
	
	LoadTex_CI4(256, 8, healthbar_tex + (128 * 8) * 1);
	PutBitmap(&rcBr, 40, 40);
	
	LoadTex_CI4(256, 8, healthbar_tex + (128 * 8) * 0);
	PutBitmap(&rcLife, 40, 40);
	
	PutNumber4(8, 40, gMC.lifeBr, FALSE);
}
