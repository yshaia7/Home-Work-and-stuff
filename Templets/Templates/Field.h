#pragma once
#include "BaseField.h"
#include <typeinfo>

template <class T>
class Field : public BaseField
{
public:
	Field(string inputQuestion) : BaseField::BaseField(inputQuestion) {}; //Constuctor
	~Field() {}; //Destuctor
	void addValidator(BaseValidator<T>* newValidator) { m_fieldValidator.push_back(newValidator); } //Add new validator to vector
	void print() { std::cout << m_inputQuestion << " = " << m_input; } //Print field
	void turnFalse() { m_validity = false; } //Turn field false
	T getInput() { return m_input; }; //Return user input from field
	void checkFieldError(); //Check if the field is correct
	void input(); //Input to field

private:
	T m_input; //The field entry
	std::vector<BaseValidator<T>*> m_fieldValidator; //Vector of validators relevant to the field
};

//-------------------------------------------------------------

template<class T>
void Field<T>::input()
{
	std::cout << m_inputQuestion << std::endl;
	std::cin >> m_input;
	for (size_t i = 0; i < m_fieldValidator.size(); i++) //Check field validity right after input
		if (!m_fieldValidator[i]->validate(m_input))
			m_validity = false;
		else
			m_validity = true;
}

//-------------------------------------------------------------

template<class T>
void Field<T>::checkFieldError()
{
	if (!getValidity()) //Return error message if needed
		for (size_t i = 0; i < m_fieldValidator.size(); i++)
		{
			std::cout << m_fieldValidator[i]->errorMessage();
			std::cout << "		";
		}
}