#include <nusys.h>
#include <ultra64.h>

#include "mem.h"
#include "draw.h"
#include "keycontrol.h"
#include "game.h"
#include "sound.h"
#include "profile.h"
#include "npctbl.h"

static BOOL run_game;

static const char *cont_error = "NO CONTROLLER";
static const char *eeprom_error = "16K EEPROM REQUIRED FOR SAVING";
static u16 error_blink = 0;

//#define MEM_DEBUG
//#define GLIST_DEBUG
//#define FRAME_DEBUG
//#define NPC_DEBUG

#ifdef NPC_DEBUG
static u32 npcs_implemented;
#endif

extern u8 *stage_map;

void VBlankCallback(int pending)
{
	if (!run_game)
		return;
	
	const char *error;
	#if (defined(MEM_DEBUG) || defined(GLIST_DEBUG) || defined(FRAME_DEBUG) || defined(NPC_DEBUG))
		char debug[0x80];
		s32 dbg_y = 50;
		#ifdef GLIST_DEBUG
			static size_t glistp_size = 0;
		#endif
		#ifdef FRAME_DEBUG
			static size_t frames = 0;
		#endif
	#endif
	
	//Update game
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
				PutText((SCREEN_WIDTH - GetTextWidth(error)) / 2 + 1, SCREEN_HEIGHT - 64 + 1, error, RGB(0x00, 0x00, 0x00));
				PutText((SCREEN_WIDTH - GetTextWidth(error)) / 2,     SCREEN_HEIGHT - 64,     error, RGB(0xFF, 0xFF, 0xFF));
			}
		}
		
		#ifdef MEM_DEBUG
			//Draw memory debug
			size_t used, size;
			Mem_GetStat(&used, &size);
			sprintf(debug, "mem: 0x%X/0x%X", used, size);
			PutText(17, dbg_y + 1, debug, RGB(0x00, 0x00, 0x00));
			PutText(16, dbg_y, debug, RGB(0xFF, 0xFF, 0xFF));
			dbg_y += 16;
		#endif
		
		#ifdef GLIST_DEBUG
			//Draw glist debug
			sprintf(debug, "glistp: 0x%X/0x%X", glistp_size, GLIST_LENGTH);
			PutText(17, dbg_y + 1, debug, RGB(0x00, 0x00, 0x00));
			PutText(16, dbg_y, debug, RGB(0xFF, 0xFF, 0xFF));
			dbg_y += 16;
		#endif
		
		#ifdef FRAME_DEBUG
			//Draw frame debug
			sprintf(debug, "frame: %d", frames);
			PutText(17, dbg_y + 1, debug, RGB(0x00, 0x00, 0x00));
			PutText(16, dbg_y, debug, RGB(0xFF, 0xFF, 0xFF));
			dbg_y += 16;
			frames++;
		#endif
		
		#ifdef NPC_DEBUG
			//Draw NPC debug
			sprintf(debug, "NPCs implemented: %d/361", npcs_implemented);
			PutText(17, dbg_y + 1, debug, RGB(0x00, 0x00, 0x00));
			PutText(16, dbg_y, debug, RGB(0xFF, 0xFF, 0xFF));
			dbg_y += 16;
		#endif
		
		//End frame
		EndFrame();
		#ifdef GLIST_DEBUG
			glistp_size = (glistp - glist);
		#endif
	}
}

static u8 mem_heap[0x10000];
void mainproc(void)
{
	//Don't run game until initialized
	run_game = FALSE;
	
	#ifdef NPC_DEBUG
		//Get NPCs implemented
		npcs_implemented = 0;
		for (u32 i = 0; i < 361; i++)
			if (gpNpcFuncTbl[i].act != NULL || gpNpcFuncTbl[i].put != NULL)
				npcs_implemented++;
	#endif
	
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
	run_game = TRUE;
	
	while (1);
}
