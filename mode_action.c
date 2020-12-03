#include "mode_action.h"
#include "draw.h"
#include "mychar.h"
#include "mychit.h"
#include "stage.h"
#include "mapname.h"
#include "keycontrol.h"

static s32 floor_y;

void ModeAction_Init()
{
	InitMyChar();
	TransferStage(13, 94, 10, 8);
	floor_y = gMC.y;
	StartMapName();
}

GameMode ModeAction_Proc()
{
	ActMyChar(TRUE);
	ResetMyCharFlag();
	HitMyCharMap();
	AnimationMyChar(TRUE);
	return GameMode_Action;
}

void ModeAction_Draw()
{
	static s32 fx = 0, fy = 0;
	fx += ((gMC.tgt_x - 320 * 0x100) - fx) / 16;
	fy += ((gMC.tgt_y - 240 * 0x100) - fy) / 16;
	CortBox(&grcFull, RGB(0x00, 0x00, 0x20));
	UpdateMapPlane(fx, fy);
	PutStage_Back(fx, fy);
	PutMyChar(fx, fy);
	PutStage_Front(fx, fy);
	PutMapName(FALSE);
}

void ModeAction_Quit()
{
	
}
