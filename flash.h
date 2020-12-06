#ifndef FLASH_H
#define FLASH_H

#include <ultra64.h>

//Flash functions
void SetFlash(s32 x, s32 y, s32 mode);
void ActFlash(s32 flx, s32 fly);
void PutFlash();
void ResetFlash();

#endif
