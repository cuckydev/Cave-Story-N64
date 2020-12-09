#include "mode_action.h"
#include "draw.h"
#include "mychar.h"
#include "mycparam.h"
#include "mychit.h"
#include "npchar.h"
#include "npchit.h"
#include "caret.h"
#include "bullet.h"
#include "bulhit.h"
#include "stage.h"
#include "mapname.h"
#include "keycontrol.h"
#include "frame.h"
#include "flash.h"
#include "textscr.h"
#include "fade.h"
#include "armsitem.h"
#include "valueview.h"
#include "shoot.h"
#include "back.h"
#include "bosslife.h"

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
		ActValueView();
		ActBack();
		
		//Collision detection
		ResetMyCharFlag();
		HitMyCharMap();
		HitMyCharNpChar();
		HitNpCharMap();
		HitBulletMap();
		HitNpCharBullet();
		
		//Update bullets and carets
		if (g_GameFlags & 2)
			ShootBullet();
		ActBullet();
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
	if (!(g_GameFlags & 4))
	{
		if (gMC.equip & EQUIP_MAP && gKeyTrg & gKeyMap)
			return GameMode_MiniMap;
	}
	
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
	
	//Draw map
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
	
	//Draw HUD
	PutBossLife();
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
