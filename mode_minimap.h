#ifndef MODE_MINIMAP_H
#define MODE_MINIMAP_H

#include "game.h"

extern GameMode minimap_return;

void ModeMiniMap_Init();
GameMode ModeMiniMap_Proc();
void ModeMiniMap_Draw();
void ModeMiniMap_Quit();

#endif
