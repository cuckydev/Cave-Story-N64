#include "mode_opening.h"
#include "draw.h"
#include "keycontrol.h"
#include "mychar.h"
#include "mychit.h"
#include "npchar.h"
#include "npchit.h"
#include "caret.h"
#include "stage.h"
#include "map.h"
#include "mapname.h"
#include "frame.h"
#include "fade.h"
#include "textscr.h"

static s32 wait;
static u8 black_time;

void ModeOpening_Init()
{
	//Initialize game
	InitNpChar();
	InitCaret();
	//InitStar();
	InitFade();
	//InitBossLife();
	//ChangeMusic(MUS_SILENCE);
	TransferStage(72, 100, 3, 3);
	SetFrameTargetMyChar(16);
	SetFadeMask();
	
	g_GameFlags = 3;
	
	CutNoise();
	
	//Initialize timers
	wait = 0;
	black_time = 0;
}

GameMode ModeOpening_Proc()
{
	if (!(black_time & 0x80))
	{
		//Go to title after 500 frames or when Ok is pressed
		if ((wait++ >= 500) || (gKeyTrg & gKeyOk))
		{
			black_time = 30 | 0x80;
			return GameMode_Opening;
		}
		
		//Update everything
		ActNpChar();
		//ActBossChar();
		//ActBack();
		ResetMyCharFlag();
		HitMyCharMap();
		HitMyCharNpChar();
		//HitMyCharBoss();
		HitNpCharMap();
		//HitBossMap();
		//HitBossBullet();
		ActCaret();
		MoveFrame3();
		ProcFade();
		
		TextScriptProc();
	}
	else
	{
		//Draw a black screen for half a second before going to title screen
		if (!(--black_time & 0x80))
			return GameMode_Title;
	}
	
	return GameMode_Opening;
}

void ModeOpening_Draw()
{
	s32 fx, fy;
	
	if (!(black_time & 0x80))
	{
		//Draw map
		CortBox(&grcFull, RGB(0x00, 0x00, 0x00));
		
		UpdateMapPlane(fx, fy);
		PutStage_Back(fx, fy);
		PutNpChar(fx, fy);
		PutStage_Front(fx, fy);
		PutCaret(fx, fy);
		
		//Draw fade and HUD
		PutFade();
		PutMapName(FALSE);
		PutTextScript();
	}
	else
	{
		//Draw a black screen for half a second before going to title screen
		CortBox(&grcFull, RGB(0x00, 0x00, 0x00));
	}
}

void ModeOpening_Quit()
{
	
}
