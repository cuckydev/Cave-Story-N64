#include "game.h"
#include "rand.h"
#include "draw.h"


//Game globals
s32 g_GameFlags = 3;

//Game modes
GameMode mode;

#include "mode_opening.h"
#include "mode_title.h"
#include "mode_action.h"

void (*mode_init[GameMode_Num])() = {
	NULL,
	ModeOpening_Init,
	ModeTitle_Init,
	ModeAction_Init,
	NULL,
	NULL,
	NULL,
};
GameMode (*mode_proc[GameMode_Num])() = {
	NULL,
	ModeOpening_Proc,
	ModeTitle_Proc,
	ModeAction_Proc,
	NULL,
	NULL,
	NULL,
};
void (*mode_draw[GameMode_Num])() = {
	NULL,
	ModeOpening_Draw,
	ModeTitle_Draw,
	ModeAction_Draw,
	NULL,
	NULL,
	NULL,
};
void (*mode_quit[GameMode_Num])() = {
	NULL,
	ModeOpening_Quit,
	ModeTitle_Quit,
	ModeAction_Quit,
	NULL,
	NULL,
	NULL,
};

static void Error_InvalidGameMode()
{
	//Draw red screen (scary!)
	CortBox(&grcFull, RGB(0xFF, 0x00, 0x00));
	
	//Draw error text
	static u16 font_tlut[] = {
		0x0000, GPACK_RGBA5551(0xFF, 0xFF, 0xFF, 1),
	};
	char text[0x80];
	sprintf(text, "INVALID GAME MODE (%d)", mode);
	PutText((SCREEN_WIDTH - GetTextWidth(text)) / 2, (SCREEN_HEIGHT - 10) / 2, text, font_tlut);
}

//Game functions
s32 Random(s32 min, s32 max)
{
	const s32 range = max - min + 1;
	return (rand() % range) + min;
}

void InitGame()
{
	//Start in opening game mode
	mode = GameMode_Opening;
	if (mode_init[mode] != NULL)
		mode_init[mode]();
}

void Game()
{
	//Run mode process
	GameMode next_mode;
	while (1)
	{
		//Run current mode process
		if (mode_proc[mode] != NULL)
			next_mode = mode_proc[mode]();
		else
			break;
		
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
	
	//Draw mode
	if (mode_draw[mode] != NULL)
		mode_draw[mode]();
	else
		Error_InvalidGameMode();
}
