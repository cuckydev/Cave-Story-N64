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
	
	//Animate player
	AnimationMyChar((g_GameFlags & 2) != 0);
	
	return GameMode_Action;
}

void ModeAction_Draw()
{
	s32 fx, fy;
	GetFramePosition(&fx, &fy);
	CortBox(&grcFull, RGB(0x00, 0x00, 0x20));
	UpdateMapPlane(fx, fy);
	PutStage_Back(fx, fy);
	PutNpChar(fx, fy);
	PutMyChar(fx, fy);
	PutStage_Front(fx, fy);
	PutCaret(fx, fy);
	PutMapName(FALSE);
}

void ModeAction_Quit()
{
	
}
