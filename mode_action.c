#include "mode_action.h"
#include "draw.h"
#include "mychar.h"
#include "mycparam.h"
#include "mychit.h"
#include "npchar.h"
#include "npchit.h"
#include "caret.h"
#include "stage.h"
#include "mapname.h"
#include "keycontrol.h"
#include "frame.h"
#include "flash.h"
#include "textscr.h"
#include "fade.h"
#include "armsitem.h"

void ModeAction_Init()
{
	
}

GameMode ModeAction_Proc()
{
	s32 fx, fy;
	
	if (g_GameFlags & 1)
	{
		//Update game
		ActMyChar((g_GameFlags & 2) != 0);
		ActNpChar();
		
		//Collision detection
		ResetMyCharFlag();
		HitMyCharMap();
		HitMyCharNpChar();
		HitNpCharMap();
		
		//Update carets
		ActCaret();
		
		//Move frame
		MoveFrame3();
		GetFramePosition(&fx, &fy);
		ActFlash(fx, fy);
		
		//Animate player
		AnimationMyChar((g_GameFlags & 2) != 0);
	}
	
	//Update fading
	ProcFade();
	
	//Handle additional input
	if (g_GameFlags & 2)
	{
		if (gKeyTrg & gKeyArms)
			RotationArms();
		else if (gKeyTrg & gKeyArmsRev)
			RotationArmsRev();
	}
	
	//Run text script
	TextScriptProc();
	
	return GameMode_Action;
}

void ModeAction_Draw()
{
	//Get frame position
	s32 fx, fy;
	GetFramePosition(&fx, &fy);
	
	//Draw blue backing
	CortBox(&grcFull, RGB(0x00, 0x00, 0x20));
	
	//Draw map
	UpdateMapPlane(fx, fy);
	PutStage_Back(fx, fy);
	PutNpChar(fx, fy);
	PutMyChar(fx, fy);
	PutStage_Front(fx, fy);
	PutFlash();
	PutCaret(fx, fy);
	
	//Draw HUD
	PutFade();
	PutMapName(FALSE);
	if (g_GameFlags & 2)
	{
		PutMyLife(TRUE);
		PutArmsEnergy(TRUE);
		PutMyAir((SCREEN_WIDTH / 2) - 40, (SCREEN_HEIGHT / 2) - 16);
		PutActiveArmsList();
	}
	PutTextScript();
}

void ModeAction_Quit()
{
	
}
