#include <nusys.h>
#include <ultra64.h>

#include "mem.h"
#include "draw.h"
#include "keycontrol.h"
#include "game.h"
#include "sound.h"
#include "profile.h"

static const char *cont_error = "NO CONTROLLER";
static const char *eeprom_error = "16K EEPROM REQUIRED FOR SAVING";
static u16 error_front_tlut[] = {
	0x0000, GPACK_RGBA5551(0xFF, 0x00, 0x00, 1),
};
static u16 error_back_tlut[] = {
	0x0000, GPACK_RGBA5551(0x00, 0x00, 0x00, 1),
};
static u16 error_blink = 0;;

void VBlankCallback(int pending)
{
	const char *error;
	char debug[0x80];
	
	if (pending < 1)
	{
		//Handle input
		GetKey();
		
		//Start frame
		StartFrame();
		
		//Draw game
		Game();
		
		//Draw error message
		if (error_blink < 0x100 && (++error_blink & 0x10))
		{
			if (gKey & INPUT_NOCON)
				error = cont_error;
			else if (!gGoodEEPROM)
				error = eeprom_error;
			else
				error = NULL;
			if (error != NULL)
			{
				PutText((SCREEN_WIDTH - GetTextWidth(error)) / 2 + 1, SCREEN_HEIGHT - 64 + 1, error, error_back_tlut);
				PutText((SCREEN_WIDTH - GetTextWidth(error)) / 2,     SCREEN_HEIGHT - 64,     error, error_front_tlut);
			}
		}
		
		#ifdef GLIST_DEBUG
			//Draw glist debug
			sprintf(debug, "glistp: 0x%X/0x%X", glistp - glist, GLIST_LENGTH);
			PutText(25, 81, debug, error_back_tlut);
			PutText(24, 80, debug, error_front_tlut);
		#endif
		
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
