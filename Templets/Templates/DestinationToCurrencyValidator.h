#pragma once
#include "ComplexValidator.h"

template <class T, class T2>
class DestinationToCurrencyValidator : public ComplexValidator<T, T2>
{
public:
	DestinationToCurrencyValidator(T* chosenDest, T2* chosenCurrency) :m_destination(chosenDest), m_currency(chosenCurrency) {} //Constructor
	~DestinationToCurrencyValidator() {} //Detructor
	bool validate(); //Check validity of field
	std::string errorMessage() { return "Destination and currency don't match"; } //Return error string
	void invalidateFields(); //Mark field as invalid

private:
	T* m_destination; //Destination field
	T2* m_currency; //Currency field
};

//-------------------------------------------------------------

template <class T, class T2>
bool DestinationToCurrencyValidator<T, T2>::validate()
{
	int destination = m_destination->getInput().getValue();
	int currency = m_currency->getInput().getValue();
	if ((destination == 1 || destination == 2) && currency == 3 || //Check if both fields are in the correct ranges
		destination == 3 && currency == 2)
		return false;
	return true;
}

//-------------------------------------------------------------

template <class T, class T2>
void DestinationToCurrencyValidator<T, T2>::invalidateFields()
{
	m_destination->turnFalse();
	m_currency->turnFalse();
}