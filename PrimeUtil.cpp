// DO NOT CHANGE AND DO NOT SUBMIT
#include "PrimeUtil.h"

bool PrimeUtil::prime(int m)
{
	for (int i = 2; i < (int)sqrt(m); i++)
		if (m % i == 0)
			return false;
	return true;
}