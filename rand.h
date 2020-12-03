#ifndef RAND_H
#define RAND_H

#include <ultra64.h>

//Random max constant
#define RAND_MAX 0x7FFF

//Random functions
void srand(u32 seed);
s32 rand();

#endif
