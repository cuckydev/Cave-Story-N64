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
static u16 error_blink = 0;

//#define MEM_DEBUG
//#define GLIST_DEBUG

void VBlankCallback(int pending)
{
	const char *error;
	#if (defined(MEM_DEBUG) || defined(GLIST_DEBUG))
		char debug[0x80];
		s32 dbg_y = 64;
		#ifdef GLIST_DEBUG
			static size_t glistp_size = 0;
		#endif
	#endif
	
	//Update game
	GetKey();
	Game_Update();
	
	if (pending < 1)
	{
		//Start frame
		StartFrame();
		
		//Draw game
		Game_Draw();
		
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
		
		#ifdef MEM_DEBUG
			//Draw memory debug
			size_t used, size;
			Mem_GetStat(&used, &size);
			sprintf(debug, "mem: 0x%X/0x%X", used, size);
			PutText(25, dbg_y + 1, debug, error_back_tlut);
			PutText(24, dbg_y, debug, error_front_tlut);
			dbg_y += 16;
		#endif
		
		#ifdef GLIST_DEBUG
			//Draw glist debug
			sprintf(debug, "glistp: 0x%X/0x%X", glistp_size, GLIST_LENGTH);
			PutText(25, dbg_y + 1, debug, error_back_tlut);
			PutText(24, dbg_y, debug, error_front_tlut);
			dbg_y += 16;
		#endif
		
		//End frame
		EndFrame();
		#ifdef GLIST_DEBUG
			glistp_size = (glistp - glist);
		#endif
	}
}

static u8 mem_heap[0x4000];
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
