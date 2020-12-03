#ifndef INPUT_H
#define INPUT_H

#include <ultra64.h>

typedef u16 InputField;
#define INPUT_LEFT  (1 << 0)
#define INPUT_UP    (1 << 1)
#define INPUT_RIGHT (1 << 2)
#define INPUT_DOWN  (1 << 3)
#define INPUT_A     (1 << 4)
#define INPUT_B     (1 << 5)
#define INPUT_START (1 << 6)
#define INPUT_L     (1 << 7)
#define INPUT_R     (1 << 8)
#define INPUT_Z     (1 << 9)
#define INPUT_NOCON (1 << 10)

void InitDirectInput();
u16 GetJoystickStatus();

#endif
