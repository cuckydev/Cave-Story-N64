#include "mode_action.h"
#include "draw.h"
#include "mychar.h"
#include "mychit.h"
#include "npchar.h"
#include "caret.h"
#include "stage.h"
#include "mapname.h"
#include "keycontrol.h"
#include "frame.h"
#include "textscr.h"
#include "fade.h"

void ModeAction_Init()
{
	
}

GameMode ModeAction_Proc()
{
	//Update game
	ActMyChar((g_GameFlags & 2) != 0);
	ActNpChar();
	
	//Collision detection
	ResetMyCharFlag();
	HitMyCharMap();
	
	//Update carets
	ActCaret();
	
	//Move frame
	MoveFrame3();
	
	//Update fading
	ProcFade();
	
	//Animate player
	AnimationMyChar((g_GameFlags & 2) != 0);
	
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
	PutCaret(fx, fy);
	
	//Draw HUD
	PutFade();
	PutMapName(FALSE);
	PutTextScript();
}

void ModeAction_Quit()
{
	
}