#include <nusys.h>
#include <ultra64.h>

#include "mem.h"
#include "draw.h"
#include "keycontrol.h"
#include "game.h"
#include "sound.h"
#include "profile.h"

void VBlankCallback(int pending)
{
	static u16 error_front_tlut[] = {
		0x0000, GPACK_RGBA5551(0xFF, 0x00, 0x00, 1),
	};
	static u16 error_back_tlut[] = {
		0x0000, GPACK_RGBA5551(0x00, 0x00, 0x00, 1),
	};
	static const char *cont_error = "NO CONTROLLER";
	static const char *eeprom_error = "16K EEPROM REQUIRED FOR SAVING";
	const char *error = NULL;
	static u16 blink;
	
	if (pending < 1)
	{
		//Handle input
		GetKey();
		
		//Start frame
		StartFrame();
		
		//Draw game
		Game();
		
		//Draw error message
		if (blink < 0x100)
		{
			if (gKey & INPUT_NOCON)
				error = cont_error;
			else if (!gGoodEEPROM)
				error = eeprom_error;
			if ((++blink & 0x10) && error != NULL)
			{
				PutText((SCREEN_WIDTH - GetTextWidth(error)) / 2 + 1, SCREEN_HEIGHT - 64 + 1, error, error_back_tlut);
				PutText((SCREEN_WIDTH - GetTextWidth(error)) / 2,     SCREEN_HEIGHT - 64,     error, error_front_tlut);
			}
		}
		
		//End frame
		EndFrame();
	}
}

static u8 mem_heap[0x80000];
void mainproc(void)
{
	//Initialize memory heap
	if (Mem_Init((void*)mem_heap, sizeof(mem_heap)))
		return;
	
	//Initialize sub-systems
	InitDirectDraw((NUGfxFunc)VBlankCallback);
	InitDirectInput();
	InitDirectSound();
	InitProfile();
	
	//Start game
	InitGame();
	StartDirectDraw();
	
	while (1);
}
