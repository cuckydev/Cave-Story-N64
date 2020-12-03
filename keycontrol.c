#include "keycontrol.h"

//Key state
InputField gKey = 0, gKeyTrg = 0;

//Key mappings
InputField gKeyJump = INPUT_A;
InputField gKeyShot = INPUT_B;
InputField gKeyArms = INPUT_R;
InputField gKeyArmsRev = INPUT_L;
InputField gKeyItem = INPUT_START;
InputField gKeyMap = INPUT_Z;

InputField gKeyOk = INPUT_A;
InputField gKeyCancel = INPUT_B;

InputField gKeyLeft = INPUT_LEFT;
InputField gKeyUp = INPUT_UP;
InputField gKeyRight = INPUT_RIGHT;
InputField gKeyDown = INPUT_DOWN;

//Key control functions
void GetKey()
{
	//Get new key state
	InputField key_old = gKey;
	gKey = GetJoystickStatus();
	gKeyTrg = (gKey ^ key_old) & gKey;
}
