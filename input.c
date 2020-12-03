#include <nusys.h>
#include "input.h"

//Controller state
static NUContData cont_data[NU_CONT_MAXCONTROLLERS];
static u8 cont_pattern;

//Input interface
void InitDirectInput()
{
	//Initialize controllers
	cont_pattern = nuContInit();
}

u16 GetJoystickStatus()
{
	InputField next_input = 0;
	
	//Update controllers
	nuContDataGetExAll(cont_data);
	
	//Update keys
	if (cont_pattern & 1)
	{
		//D-Pad
		if (cont_data[0].button & L_JPAD)
			next_input |= INPUT_LEFT;
		if (cont_data[0].button & U_JPAD)
			next_input |= INPUT_UP;
		if (cont_data[0].button & R_JPAD)
			next_input |= INPUT_RIGHT;
		if (cont_data[0].button & D_JPAD)
			next_input |= INPUT_DOWN;
		
		if ((next_input & (INPUT_LEFT | INPUT_RIGHT)) == (INPUT_LEFT | INPUT_RIGHT))
			next_input &= ~(INPUT_LEFT | INPUT_RIGHT);
		if ((next_input & (INPUT_UP | INPUT_DOWN)) == (INPUT_UP | INPUT_DOWN))
			next_input &= ~(INPUT_UP | INPUT_DOWN);
		
		//Face buttons
		if (cont_data[0].button & A_BUTTON)
			next_input |= INPUT_A;
		if (cont_data[0].button & B_BUTTON)
			next_input |= INPUT_B;
		if (cont_data[0].button & START_BUTTON)
			next_input |= INPUT_START;
		
		//Triggers
		if (cont_data[0].button & L_TRIG)
			next_input |= INPUT_L;
		if (cont_data[0].button & R_TRIG)
			next_input |= INPUT_R;
		if (cont_data[0].button & Z_TRIG)
			next_input |= INPUT_Z;
		
		return next_input;
	}
	
	return INPUT_NOCON;
}
