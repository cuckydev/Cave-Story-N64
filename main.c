#include <nusys.h>
#include <ultra64.h>

#include "mem.h"
#include "draw.h"
#include "keycontrol.h"
#include "game.h"
#include "sound.h"

void VBlankCallback(int pending)
{
	if (pending < 1)
	{
		//Handle input
		GetKey();
		
		//Run game frame
		StartFrame();
		Game();
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
