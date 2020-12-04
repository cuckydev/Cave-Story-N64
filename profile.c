#include "profile.h"
#include "mychar.h"
#include "npchar.h"
#include "frame.h"
#include "stage.h"
#include "flags.h"
#include "fade.h"

//Profile functions
void SaveProfile()
{
	
}

BOOL LoadProfile()
{
	return FALSE;
}

BOOL InitializeGame()
{
	//Initialize game state
	InitMyChar();
	//gSelectedArms = 0;
	//gSelectedItem = 0;
	//ClearArmsData();
	//ClearItemData();
	//ClearPermitStage();
	InitFlags();
	
	//Load intro scene
	TransferStage(13, 200, 10, 8);
	
	//Initialize game state (stuff after stage's loaded)
	ClearFade();
	SetFrameMyChar();
	SetFrameTargetMyChar(16);
	//InitBossLife();
	CutNoise();
	//ClearValueView();
	gCurlyShoot_wait = 0;
	SetFadeMask();
	
	return TRUE;
}
