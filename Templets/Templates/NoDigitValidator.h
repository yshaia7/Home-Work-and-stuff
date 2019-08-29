#pragma once
#include "BaseValidator.h"
#include <algorithm> 

class NoDigitValidator : public BaseValidator<std::string>
{
public:
	NoDigitValidator() {} //Constructor
	~NoDigitValidator() {} //Destructor
	bool validate(std::string& str) { return !std::any_of(str.begin(), str.end(), ::isdigit); } //Check if there are any digits in the field
	std::string errorMessage() { return "Can't contain digits"; } //Return error string
};