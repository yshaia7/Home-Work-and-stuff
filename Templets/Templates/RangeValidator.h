#pragma once
#include "BaseValidator.h"

template <class T>
class RangeValidator : public BaseValidator<T>
{
public:
	RangeValidator(const int from, const int to) :m_from(from),m_to(to) {}; //Constructor
	~RangeValidator() {}; //Destructor
	bool validate(T& parameter) { return (parameter >= m_from && parameter <= m_to); } //Check if parameter is within the accepted range
	std::string errorMessage() { return "Out of range"; } //Return error message string

private:
	int m_from, m_to; //Range received during construction
};

