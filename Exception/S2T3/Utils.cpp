//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include "Utils.h"
#include <iostream>

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
int Utils::readInt(std::istream& is)
{
	int number;
	is >> number;
	if (is.fail())
	{
		throw std::exception("Invalid input. Must enter a number and not a character.\n");
	}
	return number;
}