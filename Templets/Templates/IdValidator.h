#pragma once
#include "BaseValidator.h"
#include <stdint.h>

class IdValidator : public BaseValidator<uint32_t>
{
public:
	IdValidator() {} //Constructor
	~IdValidator() {} //Destructor
	std::string errorMessage() { return "Wrong control digit or incorrect number of digits"; } //Return error message string
	bool validate(uint32_t& idNumber); //Check validity of field

private:
	int DigitSum(int num); //Check the sum of digits of a number
};

