#include "profile.h"
#include <nusys.h>
#include "mychar.h"
#include "npchar.h"
#include "frame.h"
#include "stage.h"
#include "selstage.h"
#include "flags.h"
#include "fade.h"
#include "armsitem.h"
#include "valueview.h"
#include "bosslife.h"
#include <string.h>

BOOL gGoodEEPROM;

static const char *profile_code = "CS64rv03";

#ifdef NEWGCC
	_Static_assert((sizeof(PROFILE_DATA) & 0x7) == 0, "PROFILE_DATA size must be aligned to 8 bytes");
#endif

//Profile functions
void LoadFromProfile(const PROFILE_DATA *profile)
{
	//Use profile data
	gSelectedArms = profile->select_arms;
	
	memcpy(gArmsData, profile->arms, sizeof(gArmsData));
	memcpy(gItemData, profile->items, sizeof(gItemData));
	memcpy(gPermitStage, profile->permitstage, sizeof(gPermitStage));
	memcpy(gFlagNPC, profile->flags, sizeof(gFlagNPC));
	
	//Load stage
	//ChangeMusic(profile->music);
	InitMyChar();
	TransferStage(profile->stage, 0, 0, 1);
	
	//Set character properties
	gMC.equip = profile->equip;
	gMC.direct = profile->direct;
	gMC.max_life = profile->max_life;
	gMC.life = profile->life;
	gMC.star = profile->star;
	gMC.cond = 0x80;
	gMC.air = 1000;
	gMC.lifeBr = profile->life;
	gMC.x = profile->x;
	gMC.y = profile->y;
	
	//Reset stuff
	ClearFade();
	SetFrameMyChar();
	SetFrameTargetMyChar(16);
	InitBossLife();
	CutNoise();
	//InitStar();
	ClearValueView();
	gCurlyShoot_wait = 0;
}

void InitProfile()
{
	//Initialize the EEPROM
	nuEepromMgrInit();
	gGoodEEPROM = (nuEepromCheck() == EEPROM_TYPE_16K);
}

BOOL SaveProfile()
{
	ALIGNED8 PROFILE_DATA profile;
	
	if (gGoodEEPROM)
	{
		//Set profile data
		memset(&profile, 0, sizeof(PROFILE_DATA));
		memcpy(profile.code, profile_code, sizeof(profile.code));
		profile.stage = gStageNo;
		profile.music = 0;//gMusicNo;
		profile.x = gMC.x;
		profile.y = gMC.y;
		profile.direct = gMC.direct;
		profile.max_life = gMC.max_life;
		profile.life = gMC.life;
		profile.star = gMC.star;
		profile.select_arms = gSelectedArms;
		profile.equip = gMC.equip;
		memcpy(profile.arms, gArmsData, sizeof(profile.arms));
		memcpy(profile.items, gItemData, sizeof(profile.items));
		memcpy(profile.permitstage, gPermitStage, sizeof(profile.permitstage));
		memcpy(profile.flags, gFlagNPC, sizeof(profile.flags));
		
		//Write profile data
		nuEepromWrite(0, (u8*)&profile, sizeof(profile));
		
		return TRUE;
	}
	return FALSE;
}

BOOL LoadProfile()
{
	ALIGNED8 PROFILE_DATA profile;
	
	if (gGoodEEPROM)
	{
		//Read profile data
		nuEepromRead(0, (u8*)&profile, sizeof(profile));
		
		//Verify code
		if (strncmp(profile.code, profile_code, sizeof(profile.code)))
			return FALSE;
		
		LoadFromProfile(&profile);
		return TRUE;
	}
	return FALSE;
}

BOOL HasProfile()
{
	u8 code[8];
	if (gGoodEEPROM)
	{
		//Read code
		nuEepromRead(0, code, 8);
		if (!strncmp(code, profile_code, 8))
			return TRUE;
	}
	return FALSE;
}

BOOL InitializeGame()
{
	//Initialize game state
	InitMyChar();
	gSelectedArms = 0;
	gSelectedItem = 0;
	ClearArmsData();
	ClearItemData();
	ClearPermitStage();
	InitFlags();
	
	//Load intro scene
	TransferStage(13, 200, 10, 8);
	
	//Initialize game state (stuff after stage's loaded)
	ClearFade();
	SetFrameMyChar();
	SetFrameTargetMyChar(16);
	InitBossLife();
	CutNoise();
	ClearValueView();
	gCurlyShoot_wait = 0;
	SetFadeMask();
	
	return TRUE;
}
