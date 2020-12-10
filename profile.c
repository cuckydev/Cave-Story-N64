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
#include "keycontrol.h"
#include "valueview.h"
#include "bosslife.h"
#include <string.h>

BOOL gGoodEEPROM;

static const char *profile_code = "CS64rv02";

#pragma pack(push)
#pragma pack(1)
struct PROFILE_DATA
{
	char code[8];
	u8 stage : 7;
	u8 music : 6;
	s32 x : (32 - 5);
	s32 y : (32 - 5);
	u8 direct : 1;
	u8 max_life : 8;
	u8 star : 2;
	u8 life : 8;
	u8 select_arms : 3;
	u8 equip;
	ARMS arms[ARMS_MAX];
	ITEM items[ITEM_MAX];
	PERMIT_STAGE permitstage[PERMIT_STAGE_MAX];
	u8 flags[NPC_FLAG_BYTES];
	u8 pad[3];
} profile;
#pragma pack(pop)

#ifdef __GNUC__
	_Static_assert((sizeof(struct PROFILE_DATA) & 0x7) == 0, "PROFILE_DATA size must be aligned to 8 bytes");
#else
	typedef char GLUE2(static_assertion_failed, __LINE__)[((sizeof(struct PROFILE_DATA) & 0x7) == 0) ? 1 : -1]
#endif

//Profile functions
void InitProfile()
{
	//Initialize the EEPROM
	nuEepromMgrInit();
	gGoodEEPROM = (nuEepromCheck() == EEPROM_TYPE_16K);
}

BOOL SaveProfile()
{
	if (gGoodEEPROM)
	{
		//Set profile data
		memset(&profile, 0, sizeof(profile));
		memcpy(profile.code, profile_code, sizeof(profile.code));
		profile.stage = gStageNo;
		profile.music = 0;//gMusicNo;
		profile.x = gMC.x >> 5;
		profile.y = gMC.y >> 5;
		profile.direct = (gMC.direct != 0) ? 1 : 0;
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
	if (gGoodEEPROM)
	{
		//Read profile data
		nuEepromRead(0, (u8*)&profile, sizeof(profile));
		
		//Verify code
		if (strncmp(profile.code, profile_code, sizeof(profile.code)))
			return FALSE;
		
		//Use profile data
		gSelectedArms = profile.select_arms;
		
		memcpy(gArmsData, profile.arms, sizeof(gArmsData));
		memcpy(gItemData, profile.items, sizeof(gItemData));
		memcpy(gPermitStage, profile.permitstage, sizeof(gPermitStage));
		memcpy(gFlagNPC, profile.flags, sizeof(gFlagNPC));
		
		//Load stage
		//ChangeMusic(profile.music);
		InitMyChar();
		TransferStage(profile.stage, 0, 0, 1);
		
		//Set character properties
		gMC.equip = profile.equip;
		gMC.direct = (profile.direct != 0) ? 2 : 0;
		gMC.max_life = profile.max_life;
		gMC.life = profile.life;
		gMC.star = profile.star;
		gMC.cond = 0x80;
		gMC.air = 1000;
		gMC.lifeBr = profile.life;
		gMC.x = profile.x << 5;
		gMC.y = profile.y << 5;
		
		//Reset stuff
		ClearFade();
		SetFrameMyChar();
		SetFrameTargetMyChar(16);
		InitBossLife();
		CutNoise();
		//InitStar();
		ClearValueView();
		gCurlyShoot_wait = 0;
		
		return TRUE;
	}
	return FALSE;
}

BOOL HasProfile()
{
	if (gGoodEEPROM)
	{
		//Read code
		nuEepromRead(0, (u8*)&profile, 8);
		if (!strncmp(profile.code, profile_code, sizeof(profile.code)))
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
	TransferStage(13, (gKey & gKeyMap) ? 94 : 200, 10, 8);
	
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
