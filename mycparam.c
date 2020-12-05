#include "mycparam.h"
#include "mychar.h"
#include "npchar.h"
#include "textscr.h"
#include "game.h"
#include "caret.h"
#include "armsitem.h"
#include "draw.h"

const ARMS_LEVEL gArmsLevelTable[14] =
{
	{{0,  0,  100}},
	{{30, 40, 16}},
	{{10, 20, 10}},
	{{10, 20, 20}},
	{{30, 40, 10}},
	{{10, 20, 10}},
	{{10, 20, 30}},
	{{10, 20, 5}},
	{{10, 20, 100}},
	{{30, 60, 0}},
	{{30, 60, 10}},
	{{10, 20, 100}},
	{{1,  1,  1}},
	{{40, 60, 200}}
};

//Arms
void AddExpMyChar(s32 x)
{
	int lv = gArmsData[gSelectedArms].level - 1;
	int arms_code = gArmsData[gSelectedArms].code;

	gArmsData[gSelectedArms].exp += x;

	if (lv == 2)
	{
		if (gArmsData[gSelectedArms].exp >= gArmsLevelTable[arms_code].exp[lv])
		{
			gArmsData[gSelectedArms].exp = gArmsLevelTable[arms_code].exp[lv];
			
			if (gMC.equip & EQUIP_WHIMSICAL_STAR)
			{
				if (gMC.star < 3)
					gMC.star++;
			}
		}
	}
	else
	{
		for (; lv < 2; lv++)
		{
			if (gArmsData[gSelectedArms].exp >= gArmsLevelTable[arms_code].exp[lv])
			{
				gArmsData[gSelectedArms].level++;
				gArmsData[gSelectedArms].exp = 0;
				
				if (gArmsData[gSelectedArms].code != 13)
				{
					//PlaySoundObject(27, SOUND_MODE_PLAY);
					SetCaret(gMC.x, gMC.y, CARET_LEVEL_UP, 0);
				}
			}
		}
	}
	
	if (gArmsData[gSelectedArms].code != 13)
	{
		gMC.exp_count += x;
		gMC.exp_wait = 30;
	}
	else
	{
		gMC.exp_wait = 10;
	}
}

void ZeroExpMyChar()
{
	gArmsData[gSelectedArms].level = 1;
	gArmsData[gSelectedArms].exp = 0;
}

BOOL IsMaxExpMyChar()
{
	s32 arms_code;
	
	if (gArmsData[gSelectedArms].level == 3)
	{
		arms_code = gArmsData[gSelectedArms].code;
		if (gArmsData[gSelectedArms].exp >= gArmsLevelTable[arms_code].exp[2])
			return TRUE;
	}
	
	return FALSE;
}

void ZeroArmsEnergy_All()
{
	int a;

	for (a = 0; a < ARMS_MAX; a++)
	{
		gArmsData[a].level = 1;
		gArmsData[a].exp = 0;
	}
}

void AddBulletMyChar(s32 no, s32 val)
{
	s32 a;
	
	//Missile Launcher
	a = 0;
	while (a < ARMS_MAX && gArmsData[a].code != 5)
		a++;
	
	if (a == ARMS_MAX)
	{
		//Super Missile Launcher
		a = 0;
		while (a < ARMS_MAX && gArmsData[a].code != 10)
			a++;
		if (a == ARMS_MAX)
			return;
	}
	
	gArmsData[a].num += val;
	if (gArmsData[a].num > gArmsData[a].max_num)
		gArmsData[a].num = gArmsData[a].max_num;
}

#include "data/bitmap/expbar.inc.c"
#include "data/bitmap/armsimage.inc.c"

void PutArmsEnergy(BOOL flash)
{
	static u8 add_flash;
	
	static const RECT rcPer = {96, 0, 104, 8};
	static const RECT rcLv = {80, 8, 96, 16};
	static const RECT rcNone = {80, 0, 96, 8};
	
	RECT rcExpBox = {0, 0, 40, 8};
	RECT rcExpVal = {0, 8, 0, 16};
	RECT rcExpMax = {40, 0, 80, 8};
	RECT rcExpFlash = {40, 8, 80, 16};
	
	s32 lv;
	s32 arms_code;
	s32 exp_now;
	s32 exp_next;

	if (gArmsEnergyX > 16)
		gArmsEnergyX -= 2;
	if (gArmsEnergyX < 16)
		gArmsEnergyX += 2;
	
	//Numbers
	//Draw max ammo
	if (gArmsData[gSelectedArms].max_num)
	{
		PutNumber4(gArmsEnergyX + 32, 16, gArmsData[gSelectedArms].num, FALSE);
		PutNumber4(gArmsEnergyX + 32, 24, gArmsData[gSelectedArms].max_num, FALSE);
	}
	else
	{
		LoadTLUT_CI4(expbar_tlut);
		LoadTex_CI4(128, 16, expbar_tex);
		PutBitmap(&rcNone, gArmsEnergyX + 48, 16);
		PutBitmap(&rcNone, gArmsEnergyX + 48, 24);
	}
	
	//Draw labels
	if (flash == TRUE && (gMC.shock / 2) % 2)
		return;
	
	if (gArmsData[gSelectedArms].max_num)
	{
		LoadTLUT_CI4(expbar_tlut);
		LoadTex_CI4(128, 16, expbar_tex);
	}
	PutBitmap(&rcPer, gArmsEnergyX + 32, 24);
	PutBitmap(&rcLv, gArmsEnergyX, 32);
	PutNumber4(gArmsEnergyX - 8, 32, gArmsData[gSelectedArms].level, FALSE);
	
	lv = gArmsData[gSelectedArms].level - 1;
	arms_code = gArmsData[gSelectedArms].code;
	exp_now = gArmsData[gSelectedArms].exp;
	exp_next = gArmsLevelTable[arms_code].exp[lv];
	
	if (lv < 0)
		lv = 0;
	
	//Draw experience bar
	LoadTLUT_CI4(expbar_tlut);
	LoadTex_CI4(128, 16, expbar_tex);
	
	PutBitmap(&rcExpBox, gArmsEnergyX + 24, 32);
	if (lv == 2 && gArmsData[gSelectedArms].exp == gArmsLevelTable[arms_code].exp[lv])
	{
		PutBitmap(&rcExpMax, gArmsEnergyX + 24, 32);
	}
	else
	{
		if (exp_next != 0)
			rcExpVal.right += (exp_now * 40) / exp_next;
		else
			rcExpVal.right = 0;
		PutBitmap(&rcExpVal, gArmsEnergyX + 24, 32);
	}
	
	if (gMC.exp_wait && ((add_flash++ / 2) % 2))
		PutBitmap(&rcExpFlash, gArmsEnergyX + 24, 32);
}

void PutActiveArmsList()
{
	s32 x;
	s32 a;
	RECT rect = {0, 0, 0, 16};
	
	s32 arms_num = 0;
	while (gArmsData[arms_num].code != 0)
		arms_num++;
	
	if (arms_num == 0)
		return;
	
	LoadTLUT_CI4(armsimage_tlut);
	LoadTex_CI4(256, 16, armsimage_tex);
	for (a = 0; a < arms_num; ++a)
	{
		//Get X position to draw at
		x = ((a - gSelectedArms) * 16) + gArmsEnergyX;
		
		if (x < 8)
			x += 48 + (arms_num * 16);
		else if (x >= 24)
			x += 48;
		
		if (x >= 72 + ((arms_num - 1) * 16))
			x -= 48 + (arms_num * 16);
		if (x < 72 && x >= 24)
			x -= 48;
		
		//Draw icon
		rect.left = gArmsData[a].code * 16;
		rect.right = rect.left + 16;
		PutBitmap(&rect, x, 16);
	}
}

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

void DamageMyChar(s32 damage)
{
	if (!(g_GameFlags & 2))
		return;
	
	if (gMC.shock)
		return;
	
	//Damage player
	//PlaySoundObject(16, SOUND_MODE_PLAY);
	gMC.cond &= ~1;
	gMC.shock = 128;
	
	if (gMC.unit != 1)
		gMC.ym = -0x400;
	
	gMC.life -= damage;
	
	//Lose a whimsical star
	if (gMC.equip & EQUIP_WHIMSICAL_STAR && gMC.star > 0)
		gMC.star--;
	
	//Lose experience
	if (gMC.equip & EQUIP_ARMS_BARRIER)
		gArmsData[gSelectedArms].exp -= damage;
	else
		gArmsData[gSelectedArms].exp -= damage * 2;
	
	while (gArmsData[gSelectedArms].exp < 0)
	{
		if (gArmsData[gSelectedArms].level > 1)
		{
			gArmsData[gSelectedArms].level--;
			
			int lv = gArmsData[gSelectedArms].level - 1;
			int arms_code = gArmsData[gSelectedArms].code;
			
			gArmsData[gSelectedArms].exp = gArmsLevelTable[arms_code].exp[lv] + gArmsData[gSelectedArms].exp;
			
			if (gMC.life > 0 && gArmsData[gSelectedArms].code != 13)
				SetCaret(gMC.x, gMC.y, CARET_LEVEL_UP, 2);
		}
		else
		{
			gArmsData[gSelectedArms].exp = 0;
		}
	}
	
	//Tell player how much damage was taken
	//SetValueView(&gMC.x, &gMC.y, -damage);
	
	//Death
	if (gMC.life <= 0)
	{
		//PlaySoundObject(17, SOUND_MODE_PLAY);
		gMC.cond = 0;
		SetDestroyNpChar(gMC.x, gMC.y, 0x1400, 0x40);
		StartTextScript(40);
	}
}

#include "data/bitmap/healthbar.inc.c"

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
