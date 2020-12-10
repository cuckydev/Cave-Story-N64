#include "mode_camp.h"
#include "armsitem.h"
#include "textscr.h"
#include "keycontrol.h"
#include "draw.h"
#include "sound.h"
#include "mode_minimap.h"

#include "data/armsitem_script.inc.c"

static const char *prev_script;

static BOOL gCampActive;
static s32 gCampTitleY;
static u32 flash;

static BOOL no_init = FALSE;

void ModeCamp_Init()
{
	if (!no_init)
	{
		//Load inventory script
		prev_script = GetTextScript();
		LoadTextScript(armsitem_script);
		
		//Initialize inventory state
		gCampActive = FALSE;
		gCampTitleY = (SCREEN_HEIGHT / 2) - 96;
		
		gSelectedItem = 0;
		
		//Run initial event
		if (gArmsData[0].code != 0)
			StartTextScript(1000 + gArmsData[gSelectedArms].code);
		else
			StartTextScript(5000 + gItemData[gSelectedItem].code);
	}
	no_init = FALSE;
}

void MoveCampCursor()
{
	BOOL bChange;
	
	//Compute the current amount of weapons and items
	s32 arms_num = 0;
	s32 item_num = 0;
	while (gArmsData[arms_num].code != 0)
		++arms_num;
	while (gItemData[item_num].code != 0)
		++item_num;
	
	if (arms_num == 0 && item_num == 0)
		return;	//Empty inventory
	
	//True if we're currently changing cursor position
	bChange = FALSE;
	
	if (!gCampActive)
	{
		//Handle selected weapon
		if (gKeyTrg & gKeyLeft)
		{
			gSelectedArms--;
			bChange = TRUE;
		}
		
		if (gKeyTrg & gKeyRight)
		{
			gSelectedArms++;
			bChange = TRUE;
		}
		
		if (gKeyTrg & (gKeyUp | gKeyDown))
		{
			//If there are any items, we're changing to the items section, since the weapons section has only 1 row
			if (item_num != 0)
				gCampActive = TRUE;
			bChange = TRUE;
		}
		
		//Loop around gSelectedArms if needed
		if (gSelectedArms < 0)
			gSelectedArms = arms_num - 1;
		if (gSelectedArms > arms_num - 1)
			gSelectedArms = 0;
	}
	else
	{
		//Handle selected item
		if (gKeyTrg & gKeyLeft)
		{
			if (gSelectedItem % 6 == 0)
				gSelectedItem += 5;
			else
				gSelectedItem -= 1;
			bChange = TRUE;
		}
		
		if (gKeyTrg & gKeyRight)
		{
			if (gSelectedItem == item_num - 1)
				gSelectedItem = (gSelectedItem / 6) * 6;	//Round down to multiple of 6
			else if (gSelectedItem % 6 == 5)
				gSelectedItem -= 5;	//Loop around row
			else
				gSelectedItem += 1;
			bChange = TRUE;
		}
		
		if (gKeyTrg & gKeyUp)
		{
			if (gSelectedItem / 6 == 0)
				gCampActive = FALSE;	//We're on the first row, transition to weapons
			else
				gSelectedItem -= 6;
			bChange = TRUE;
		}
		
		if (gKeyTrg & gKeyDown)
		{
			if (gSelectedItem / 6 == (item_num - 1) / 6)
				gCampActive = FALSE;	//We're on the last row, transition to weapons
			else
				gSelectedItem += 6;
			bChange = TRUE;
		}
		
		if (gSelectedItem >= item_num)
			gSelectedItem = item_num - 1;	//Don't allow selecting a non-existing item
		
		if (gCampActive && gKeyTrg & gKeyOk)
			StartTextScript(6000 + gItemData[gSelectedItem].code);
	}

	if (bChange)
	{
		if (gCampActive == FALSE)
		{
			//Switch to a weapon
			PlaySoundObject(4, 1);
			if (arms_num != 0)
				StartTextScript(1000 + gArmsData[gSelectedArms].code);
			else
				StartTextScript(1000);
		}
		else
		{
			//Switch to an item
			PlaySoundObject(1, 1);
			if (item_num != 0)
				StartTextScript(5000 + gItemData[gSelectedItem].code);
			else
				StartTextScript(5000);
		}
	}
}

GameMode ModeCamp_Proc()
{
	//Handle input
	if (g_GameFlags & 2)
		MoveCampCursor();
	
	//Run TSC
	switch (TextScriptProc())
	{
		case TSCR_Restart:
			return GameMode_Opening;
		case TSCR_MiniMap:
			minimap_return = GameMode_Camp;
			no_init = TRUE;
			return GameMode_MiniMap;
		default:
			break;
	}
	
	//Move titles
	if (gCampTitleY > (SCREEN_HEIGHT / 2) - 104)
		gCampTitleY--;
	
	//Increment cursor flash
	flash++;
	
	//Check if the inventory should be closed
	if (gCampActive)
	{
		if (g_GameFlags & 2 && gKeyTrg & (gKeyCancel | gKeyItem))
			return GameMode_Action;
	}
	else
	{
		if (gKeyTrg & (gKeyOk | gKeyCancel | gKeyItem))
			return GameMode_Action;
	}
	
	return GameMode_Camp;
}

#include "data/bitmap/textbox.inc.c"
#include "data/bitmap/inventorytitle.inc.c"
#include "data/bitmap/armsimage.inc.c"
#include "data/bitmap/armscursor.inc.c"
#include "data/bitmap/expbar.inc.c"
#include "data/bitmap/itemimage.inc.c"
#include "data/bitmap/itemcursor.inc.c"

void PutCampObject()
{
	static const RECT rcBox = {0, 0, 256, 16};
	
	static const RECT rcTitle1 = {0, 0, 64, 8};
	static const RECT rcTitle2 = {0, 8, 64, 16};
	
	static const RECT rcCur1[2] = {{0, 0, 40, 40}, {40, 0, 80, 40}};
	static const RECT rcCur2[2] = {{0, 0, 32, 16}, {0, 16, 32, 32}};
	
	static const RECT rcPer = {96, 0, 104, 8};
	static const RECT rcLv = {80, 8, 96, 16};
	static const RECT rcNone = {80, 0, 96, 8};
	
	RECT rcArms = {0, 0, 0, 16}, rcItem = {0, 0, 0, 16};
	
	s32 i;
	
	//Draw frame
	LoadTLUT_CI4(textbox_tlut);
	
	LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 0);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 + 0);
	
	LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 1);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 +  16);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 +  32);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 +  48);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 +  64);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 +  80);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 +  96);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 + 112);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 + 128);
	
	LoadTex_CI4(256, 16, textbox_tex + (128 * 16) * 2);
	PutBitmap(&rcBox, (SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT / 2) - 112 + 144);
	
	//Draw titles
	LoadTLUT_CI4(inventorytitle_tlut);
	LoadTex_CI4(64, 16, inventorytitle_tex);
	
	PutBitmap(&rcTitle1, (SCREEN_WIDTH / 2) - 112, gCampTitleY);
	PutBitmap(&rcTitle2, (SCREEN_WIDTH / 2) - 112, gCampTitleY + 52);
	
	//Draw arms cursor
	LoadTLUT_CI4(armscursor_tlut);
	LoadTex_CI4(80, 40, armscursor_tex);
	if (gCampActive == FALSE)
		PutBitmap(&rcCur1[(flash / 2) % 2], (gSelectedArms * 40) + (SCREEN_WIDTH / 2) - 112, (SCREEN_HEIGHT / 2) - 96);
	else
		PutBitmap(&rcCur1[1], (gSelectedArms * 40) + (SCREEN_WIDTH / 2) - 112, (SCREEN_HEIGHT / 2) - 96);
	
	// Draw arms
	for (i = 0; i < ARMS_MAX; i++)
	{
		if (gArmsData[i].code == 0)
			break;
		
		//Get icon rect for next arms
		rcArms.left = (gArmsData[i].code % 16) * 16;
		rcArms.right = rcArms.left + 16;
		
		//Draw the icon, slash and "Lv"
		LoadTLUT_CI4(armsimage_tlut);
		LoadTex_CI4(256, 16, armsimage_tex);
		PutBitmap(&rcArms, (i * 40) + (SCREEN_WIDTH / 2) - 112, (SCREEN_HEIGHT / 2) - 96);
		
		LoadTLUT_CI4(expbar_tlut);
		LoadTex_CI4(128, 16, expbar_tex);
		PutBitmap(&rcPer, (i * 40) + (SCREEN_WIDTH / 2) - 112, (SCREEN_HEIGHT / 2) - 64);
		PutBitmap(&rcLv, (i * 40) + (SCREEN_WIDTH / 2) - 112, (SCREEN_HEIGHT / 2) - 80);
		PutNumber4((i * 40) + (SCREEN_WIDTH / 2) - 112, (SCREEN_HEIGHT / 2) - 80, gArmsData[i].level, FALSE);
		
		//Draw ammo
		if (gArmsData[i].max_num)
		{
			PutNumber4((i * 40) + (SCREEN_WIDTH / 2) - 112, (SCREEN_HEIGHT / 2) - 72, gArmsData[i].num, FALSE);
			PutNumber4((i * 40) + (SCREEN_WIDTH / 2) - 112, (SCREEN_HEIGHT / 2) - 64, gArmsData[i].max_num, FALSE);
		}
		else
		{
			LoadTLUT_CI4(expbar_tlut);
			LoadTex_CI4(128, 16, expbar_tex);
			PutBitmap(&rcNone, (i * 40) + (SCREEN_WIDTH - 192) / 2, (SCREEN_HEIGHT / 2) - 72);
			PutBitmap(&rcNone, (i * 40) + (SCREEN_WIDTH - 192) / 2, (SCREEN_HEIGHT / 2) - 64);
		}
	}
	
	//Draw items cursor
	LoadTLUT_CI4(itemcursor_tlut);
	LoadTex_CI4(32, 32, itemcursor_tex);
	if (gCampActive == TRUE)
		PutBitmap(&rcCur2[(flash / 2) % 2], ((gSelectedItem % 6) * 32) + (SCREEN_WIDTH / 2) - 112, ((gSelectedItem / 6) * 16) + (SCREEN_HEIGHT / 2) - 44);
	else
		PutBitmap(&rcCur2[1], ((gSelectedItem % 6) * 32) + (SCREEN_WIDTH / 2) - 112, ((gSelectedItem / 6) * 16) + (SCREEN_HEIGHT / 2) - 44);
	
	for (i = 0; i < ITEM_MAX; i++)
	{
		if (gItemData[i].code == 0)
			break;
		
		//Get rect for next item
		rcItem.left = (gItemData[i].code % 8) * 32;
		rcItem.right = rcItem.left + 32;
		
		//Draw item
		LoadTLUT_CI4(itemimage_tlut);
		LoadTex_CI4(256, 16, itemimage_tex + (128 * 16) * (gItemData[i].code / 8));
		PutBitmap(&rcItem, ((i % 6) * 32) + (SCREEN_WIDTH / 2) - 112, ((i / 6) * 16) + (SCREEN_HEIGHT / 2) - 44);
	}
}

#include "frame.h"
#include "back.h"
#include "map.h"
#include "npchar.h"
#include "bullet.h"
#include "mychar.h"
#include "caret.h"
#include "flash.h"
#include "valueview.h"
#include "bosslife.h"
#include "fade.h"

void ModeCamp_Draw()
{
	//TODO: draw a screen capture instead of the entire game
	s32 fx, fy;
	GetFramePosition(&fx, &fy);
	
	UpdateMapPlane(fx, fy);
	PutBack(fx, fy);
	PutStage_Back(fx, fy);
	PutNpChar(fx, fy);
	PutBullet(fx, fy);
	PutMyChar(fx, fy);
	PutStage_Front(fx, fy);
	PutFlash();
	PutCaret(fx, fy);
	PutValueView(fx, fy);
	PutBossLife();
	PutFade();
	
	//Draw inventory
	PutCampObject();
	PutTextScript();
}

void ModeCamp_Quit()
{
	if (!no_init)
	{
		//Reload stage script
		StopTextScript();
		LoadTextScript_Stage(prev_script);
		
		//Display weapon switch animation
		gArmsEnergyX = 32;
	}
}
