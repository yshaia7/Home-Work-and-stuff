#include "IdValidator.h"

bool IdValidator::validate(uint32_t& idNumber)
{
	uint32_t tempId = idNumber;
	int sum = 0, weight = 1;
	if (tempId > 999999999 || tempId < 100000000) //A valid number must have 9 digits
		return false;
	while (tempId) { //Checks whether the Control Digit is valid
		sum += DigitSum(weight * (tempId % 10));
		tempId /= 10;
		weight = 3 - weight;
	}
	return !(sum % 10);
}

//-------------------------------------------------------------

int  IdValidator::DigitSum(int num)
{
	int sum = 0;
	while (num != 0)
	{
		sum = sum + num % 10;
		num = num / 10;
	}
	return sum;
}
