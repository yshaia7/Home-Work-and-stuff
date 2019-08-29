#pragma once
#include "ComplexValidator.h"

template <class T, class T2>
class DestinationToClassValidator : public ComplexValidator<T, T2>
{
public:
	DestinationToClassValidator(T* chosenDest, T2* chosenClass) :m_destination(chosenDest), m_class(chosenClass) {}; //Constructor
	~DestinationToClassValidator() {}; //Destructor
	bool validate(); //Check validity of field
	std::string errorMessage() { return "Destination and class don't match"; } //Return error string
	void invalidateFields(); //Mark field as invalid
	
private:
	T* m_destination; //Destination field
	T2* m_class; //Class field
};

//-------------------------------------------------------------

template <class T, class T2>
bool DestinationToClassValidator<T, T2>::validate()
{
	int destination = m_destination->getInput().getValue();
	int flightClass = m_class->getInput().getValue();
	if ( !(m_destination->getValidity()) || !(m_class->getValidity()) || //Check if both fields are valid and are in the correct ranges
		((destination == 1 || destination == 2) && (flightClass == 1 || flightClass == 2)) ||
		((destination == 4 || destination == 5) && (flightClass == 2 || flightClass == 3)) ||
		(destination == 3))
		return true;
	return false;
}

//-------------------------------------------------------------

template <class T, class T2>
void DestinationToClassValidator<T, T2>::invalidateFields()
{
	m_destination->turnFalse();
	m_class->turnFalse();
}