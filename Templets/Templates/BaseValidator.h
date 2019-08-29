#pragma once
#include <string>

template <class T>
class BaseValidator
{
public:
	BaseValidator() {} //Constructor
	~BaseValidator() {} //Destructor
	virtual bool validate(T &parameter)  { return false; } //Check validity of field
	virtual bool validate()  { return false; }
	virtual void invalidateFields() {} //Mark field as invalid
	virtual std::string errorMessage() = 0; //Return error message string
};