#include "mode_stageselect.h"
#include "selstage.h"
#include "textscr.h"
#include "keycontrol.h"
#include "draw.h"
#include "sound.h"

#include "data/stageselect_script.inc.c"

static const char *prev_script;

static s32 gSelectedStage;
static s32 gStageSelectTitleY;
static u16 flash;

void ModeStageSelect_Init()
{
	//Load stage select script
	prev_script = GetTextScript();
	LoadTextScript(stageselect_script);
	
	//Initialize stage select state
	gSelectedStage = 0;
	gStageSelectTitleY = (SCREEN_HEIGHT / 2) - 66;
	
	//Run initial event
	StartTextScript(gPermitStage[gSelectedStage].index + 1000);
}

void MoveStageSelectCursor()
{
	s32 stage_num = 0;
	while (gPermitStage[stage_num].index != 0)
		stage_num++;
	
	if (stage_num == 0)
		return;
	
	if (gKeyTrg & gKeyLeft)
		--gSelectedStage;
	if (gKeyTrg & gKeyRight)
		++gSelectedStage;
	
	if (gSelectedStage < 0)
		gSelectedStage = stage_num - 1;
	if (gSelectedStage > stage_num - 1)
		gSelectedStage = 0;
	
	if (gKeyTrg & (gKeyLeft | gKeyRight))
	{
		StartTextScript(gPermitStage[gSelectedStage].index + 1000);
		PlaySoundObject(1, 1);
	}
}

GameMode ModeStageSelect_Proc()
{
	//Handle stage selecting
	MoveStageSelectCursor();
	
	//Run TSC
	switch (TextScriptProc())
	{
		case TSCR_Restart:
			return GameMode_Opening;
		default:
			break;
	}
	
	//Handle ok or cancel being pressed
	if (gKeyTrg & gKeyOk)
	{
		//Exit running event
		return GameMode_Action;
	}
	else if (gKeyTrg & gKeyCancel)
	{
		//Exit without running event
		gSelectedStage = -1;
		return GameMode_Action;
	}
	
	//Move title
	if (gStageSelectTitleY > (SCREEN_HEIGHT / 2) - 74)
		gStageSelectTitleY--;
	
	//Increment cursor flash
	flash++;
	
	return GameMode_StageSelect;
}

#include "data/bitmap/stageselecttitle.inc.c"
#include "data/bitmap/stageimage.inc.c"
#include "data/bitmap/itemcursor.inc.c"

void PutStageSelectObject()
{
	static const RECT rcTitle1 = {0, 0, 64, 8};
	static const RECT rcCur[2] = {{0, 0, 32, 16}, {0, 16, 32, 32}};
	RECT rcStage = {0, 0, 0, 16};
	s32 i;
	
	//Get stage num
	s32 stage_x;
	s32 stage_num = 0;
	while (gPermitStage[stage_num].index)
		++stage_num;
	
	//Draw title
	LoadTLUT_CI4(stageselecttitle_tlut);
	LoadTex_CI4(64, 8, stageselecttitle_tex);
	PutBitmap(&rcTitle1, (SCREEN_WIDTH - 64) / 2, gStageSelectTitleY);
	
	if (stage_num != 0)
	{
		//Get base x position
		stage_x = (SCREEN_WIDTH - (stage_num * 40)) / 2;
		
		//Draw cursor
		LoadTLUT_CI4(itemcursor_tlut);
		LoadTex_CI4(32, 32, itemcursor_tex);
		PutBitmap(&rcCur[flash / 2 % 2], stage_x + (gSelectedStage * 40) + 4, (SCREEN_HEIGHT / 2) - 56);
		
		//Draw stage images
		LoadTLUT_CI4(stageimage_tlut);
		LoadTex_CI4(256, 16, stageimage_tex);
		
		for (i = 0; i < PERMIT_STAGE_MAX; i++)
		{
			if (gPermitStage[i].index == 0)
				break;
			
			rcStage.left = gPermitStage[i].index * 32;
			rcStage.right = rcStage.left + 32;
			PutBitmap(&rcStage, stage_x + (i * 40) + 4, (SCREEN_HEIGHT / 2) - 56);
		}
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

void ModeStageSelect_Draw()
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
	
	//Draw stage select
	PutStageSelectObject();
	PutTextScript();
}

void ModeStageSelect_Quit()
{
	//Reload stage script and run selected stage's event
	StopTextScript();
	LoadTextScript_Stage(prev_script);
	if (gSelectedStage >= 0)
		JumpTextScript(gPermitStage[gSelectedStage].event);
	else
		JumpTextScript(0);
	g_GameFlags &= ~3;
}
