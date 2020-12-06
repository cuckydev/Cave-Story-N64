#ifndef VALUEVIEW_H
#define VALUEVIEW_H

#include <ultra64.h>
#include "game_def.h"

void ClearValueView();
void SetValueView(s32 *px, s32 *py, s32 value);
void ActValueView();
void PutValueView(s32 flx, s32 fly);

#endif
