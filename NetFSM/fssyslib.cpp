//=====================================================    FSSYSLIB.CPP
#include "fsacore.h"
unsigned long bit[]  = { 
	bit0, bit1, bit2, bit3, bit4, bit5, bit6, bit7, bit8, bit9, 
	bit10, bit11, bit12, bit13, bit14, bit15, bit16, bit17, bit18, bit19, 
	bit20, bit21, bit22, bit23, bit24, bit25, bit26, bit27, bit28, bit29, 
	bit30, bit31
};
unsigned long *pBit=bit;
unsigned long *pbit=bit;
bool ffs (unsigned long *d, unsigned long *num)
{
	long dat=*d;
	pBit = bit;
	if (!dat) 
		return true;
	int i=0; 
	while (!(dat & *pBit++)) 
		i++;
	*num= i; 
	return false;
}

void bbsc(int num, unsigned long *dat)
{
	*dat &=~(pBit[num]); 
}

