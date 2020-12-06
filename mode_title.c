#include "mode_title.h"
#include "draw.h"
#include "sound.h"
#include "keycontrol.h"
#include "profile.h"

#include "data/bitmap/title.inc.c"
#include "data/bitmap/title_quote.inc.c"
#include "data/bitmap/title_curly.inc.c"
#include "data/bitmap/title_toroko.inc.c"
#include "data/bitmap/title_king.inc.c"
#include "data/bitmap/title_sue.inc.c"
#include "data/bitmap/title_options.inc.c"
#include "data/bitmap/title_pixel.inc.c"
#include "data/bitmap/title_version.inc.c"

static s32 wait;
static s32 anime;
static s32 char_type;
static u8 black_time;
static BOOL bContinue;

void ModeTitle_Init()
{
	//Initialize title state
	wait = 0;
	anime = 0;
	char_type = 0;
	black_time = 0;
	bContinue = HasProfile();
}

GameMode ModeTitle_Proc()
{
	if (!(black_time & 0x80))
	{
		//Quit when OK is pressed
		if (wait >= 10)
		{
			if (gKeyTrg & gKeyOk)
			{
				PlaySoundObject(18, 1);
				black_time = 60 | 0x80;
				return GameMode_Title;
			}
		}
		else
		{
			wait++;
		}
		
		//Move cursor
		if (gKeyTrg & (gKeyUp | gKeyDown))
		{
			PlaySoundObject(1, 1);
			if (bContinue)
				bContinue = FALSE;
			else
				bContinue = TRUE;
		}
	}
	else
	{
		//Draw a black screen for a second after selecting an option
		if (!(--black_time & 0x80))
			return GameMode_Action;
	}
	return GameMode_Title;
}

void ModeTitle_Draw()
{
	static const RECT rcTitle1 = {0, 0, 128, 32};
	static const RECT rcTitle2 = {0, 0,  16, 32};
	static const RECT rcPixel = {0, 0, 128, 16};
	static const RECT rcCursor[4] = {
		{ 0, 0, 16, 16},
		{16, 0, 32, 16},
		{ 0, 0, 16, 16},
		{32, 0, 48, 16},
	};
	static const RECT rcNew =      {0,  0, 48, 16};
	static const RECT rcContinue = {0, 16, 48, 32};
	static const RECT rcVersion = {0, 0, 128, 8};
	
	if (!(black_time & 0x80))
	{
		//Draw background
		CortBox(&grcFull, RGB(0x20, 0x20, 0x20));
		
		//Draw 'Cave Story' logo
		LoadTLUT_CI4(title_tlut);
		
		LoadTex_CI4(128, 32, title_tex1);
		PutBitmap(&rcTitle1, (SCREEN_WIDTH - 144) / 2, 40);
		LoadTex_CI4(16, 32, title_tex2);
		PutBitmap(&rcTitle2, (SCREEN_WIDTH - 144) / 2 + 128, 40);
		
		//Draw version
		LoadTLUT_CI4(title_version_tlut);
		LoadTex_CI4(128, 8, title_version_tex);
		PutBitmap(&rcVersion, (SCREEN_WIDTH - 128) / 2, SCREEN_HEIGHT - 24);
		
		//Draw options
		LoadTLUT_CI4(title_options_tlut);
		LoadTex_CI4(48, 32, title_options_tex);
		PutBitmap(&rcNew, (SCREEN_WIDTH / 2) - 24, (SCREEN_HEIGHT / 2) + 8);
		PutBitmap(&rcContinue, (SCREEN_WIDTH / 2) - 24, (SCREEN_HEIGHT / 2) + 28);
		
		//Draw Pixel copyright
		LoadTLUT_CI4(title_pixel_tlut);
		LoadTex_CI4(128, 16, title_pixel_tex);
		PutBitmap(&rcPixel, (SCREEN_WIDTH - 128) / 2, SCREEN_HEIGHT - 48);
		
		//Animate cursor
		if (++anime >= 40)
			anime = 0;
		
		//Draw cursor
		switch (char_type)
		{
			case 0:
				LoadTLUT_CI4(title_quote_tlut);
				LoadTex_CI4(48, 16, title_quote_tex);
				break;
			case 1:
				LoadTLUT_CI4(title_curly_tlut);
				LoadTex_CI4(48, 16, title_curly_tex);
				break;
			case 2:
				LoadTLUT_CI4(title_toroko_tlut);
				LoadTex_CI4(48, 16, title_toroko_tex);
				break;
			case 3:
				LoadTLUT_CI4(title_king_tlut);
				LoadTex_CI4(48, 16, title_king_tex);
				break;
			case 4:
				LoadTLUT_CI4(title_sue_tlut);
				LoadTex_CI4(48, 16, title_sue_tex);
				break;
		}
		
		if (!bContinue)
			PutBitmap(&rcCursor[anime / 10], (SCREEN_WIDTH / 2) - 44, (SCREEN_HEIGHT / 2) + 7);
		else
			PutBitmap(&rcCursor[anime / 10], (SCREEN_WIDTH / 2) - 44, (SCREEN_HEIGHT / 2) + 27);
	}
	else
	{
		//Draw a black screen for a second after selecting an option
		CortBox(&grcFull, RGB(0x00, 0x00, 0x00));
	}
}

void ModeTitle_Quit()
{
	//Load or start new game
	if (!bContinue || !LoadProfile())
		InitializeGame();
}
