#include "game.h"
#include "rand.h"
#include "draw.h"
#include "keycontrol.h"

//Game globals
s32 g_GameFlags = 3;

//Game modes
GameMode mode;

#include "mode_opening.h"
#include "mode_title.h"
#include "mode_action.h"
#include "mode_camp.h"
#include "mode_minimap.h"
#include "mode_stageselect.h"

void (*mode_init[GameMode_Num])() = {
	NULL,
	ModeOpening_Init,
	ModeTitle_Init,
	ModeAction_Init,
	ModeCamp_Init,
	ModeMiniMap_Init,
	ModeStageSelect_Init,
	NULL,
};
GameMode (*mode_proc[GameMode_Num])() = {
	NULL,
	ModeOpening_Proc,
	ModeTitle_Proc,
	ModeAction_Proc,
	ModeCamp_Proc,
	ModeMiniMap_Proc,
	ModeStageSelect_Proc,
	NULL,
};
void (*mode_draw[GameMode_Num])() = {
	NULL,
	ModeOpening_Draw,
	ModeTitle_Draw,
	ModeAction_Draw,
	ModeCamp_Draw,
	ModeMiniMap_Draw,
	ModeStageSelect_Draw,
	NULL,
};
void (*mode_quit[GameMode_Num])() = {
	NULL,
	ModeOpening_Quit,
	ModeTitle_Quit,
	ModeAction_Quit,
	ModeCamp_Quit,
	ModeMiniMap_Quit,
	ModeStageSelect_Quit,
	NULL,
};

static void Error_InvalidGameMode()
{
	char text[0x80];
	
	//Draw red screen (scary!)
	CortBox(&grcFull, RGB(0xFF, 0x00, 0x00));
	
	//Draw error text
	sprintf(text, "INVALID GAME MODE (%d)", mode);
	PutText((SCREEN_WIDTH - GetTextWidth(text)) / 2, (SCREEN_HEIGHT - 10) / 2, text, RGB(0xFF, 0xFF, 0xFF));
}

//Game functions
s32 Random(s32 min, s32 max)
{
	const s32 range = max - min + 1;
	return (rand() % range) + min;
}

#include "data/bitmap/numbers.inc.c"

void PutNumber4(s32 x, s32 y, s32 value, BOOL bZero)
{
	RECT rect[10] = {
		{0,  0, 8,  8},
		{0,  8, 8, 16},
		{0, 16, 8, 24},
		{0, 24, 8, 32},
		{0, 32, 8, 40},
		{0, 40, 8, 48},
		{0, 48, 8, 56},
		{0, 56, 8, 64},
		{0, 64, 8, 72},
		{0, 72, 8, 80},
	};
	static const s32 tbl[4] = {1000, 100, 10, 1};
	
	s32 a;
	s32 sw;
	s32 offset;
	
	//Limit value
	if (value > 9999)
		value = 9999;
	
	//Go through number and draw digits
	offset = 0;
	sw = 0;
	
	LoadTLUT_CI4(numbers_tlut);
	LoadTex_CI4(16, 96, numbers_tex);
	while (offset < 4)
	{
		//Get the digit that this is
		a = 0;
		
		while (value >= tbl[offset])
		{
			value -= tbl[offset];
			++a;
			++sw;
		}
		
		//Draw digit
		if ((bZero && offset == 2) || sw != 0 || offset == 3)
			PutBitmap(&rect[a], x + 8 * offset, y);
		
		//Go to next digit
		++offset;
	}
}

void InitGame()
{
	//Start in opening game mode
	mode = GameMode_Opening;
	if (mode_init[mode] != NULL)
		mode_init[mode]();
}

void Game_Update()
{
	//Run mode process
	GameMode next_mode;
	while (1)
	{
		//Run current mode process
		if (mode_proc[mode] != NULL)
		{
			GetKey();
			next_mode = mode_proc[mode]();
		}
		else
		{
			break;
		}
		
		//Handle mode changes
		if (next_mode != mode)
		{
			//Quit current mode
			if (mode_quit[mode] != NULL)
				mode_quit[mode]();
			
			//Init new mode
			mode = next_mode;
			if (mode_init[mode] != NULL)
				mode_init[mode]();
			continue;
		}
		break;
	}
}

void Game_Draw()
{
	//Draw mode
	if (mode_draw[mode] != NULL)
		mode_draw[mode]();
	else
		Error_InvalidGameMode();
}
