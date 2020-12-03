#ifndef KEYCONTROL_H
#define KEYCONTROL_H

#include "input.h"

//Key state
extern InputField gKey, gKeyTrg;

//Key mappings
extern InputField gKeyJump;
extern InputField gKeyShot;
extern InputField gKeyArms;
extern InputField gKeyArmsRev;
extern InputField gKeyItem;
extern InputField gKeyMap;

extern InputField gKeyOk;
extern InputField gKeyCancel;

extern InputField gKeyLeft;
extern InputField gKeyUp;
extern InputField gKeyRight;
extern InputField gKeyDown;

//Key functions
void GetKey();

#endif
