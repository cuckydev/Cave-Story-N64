#include <nusys.h>
#include <ultra64.h>

#include "mem.h"
#include "draw.h"
#include "keycontrol.h"
#include "game.h"
#include "sound.h"

void VBlankCallback(int pending)
{
	static u16 font_tlut[] = {
		0x0000, GPACK_RGBA5551(0xFF, 0xFF, 0xFF, 1),
	};
	
	char test[0x80];
	if (pending < 1)
	{
		//Handle input
		GetKey();
		
		//Run game frame
		StartFrame();
		Game();
		sprintf(test, "0x%X / 0x%X", glistp - glist, GLIST_LENGTH);
		PutText(24, 24, test, font_tlut);
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
	
	//Start game
	InitGame();
	StartDirectDraw();
	
	while (1);
}
