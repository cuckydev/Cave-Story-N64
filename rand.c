#include "rand.h"

//Random functions
static u32 holdrand;

void srand(u32 seed)
{
	holdrand = seed;
}

s32 rand()
{
	holdrand = holdrand * 214013L + 2531011L;
	return ((holdrand >> 16) & 0x7FFF);
}
