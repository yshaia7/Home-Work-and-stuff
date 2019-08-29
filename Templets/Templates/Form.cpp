#include "Form.h"
#include <string>

void Form::fillForm()
{
	for (size_t i = 0; i < m_fields.size(); i++) //Fill all invalid fields
		if (!m_fields[i]->getValidity())
			m_fields[i]->input();
}

//-------------------------------------------------------------

bool Form::validateForm()
{
	bool flag = true;
	for (size_t i = 0; i < m_fields.size(); i++) //Check validity of all individual fields
		if (!m_fields[i]->getValidity())
			flag = false;

	for (size_t i = 0; i < m_validator.size(); i++) //Check validity using the complex validators
		if (!m_validator[i]->validate())
			flag = false;

	return flag;
}

//-------------------------------------------------------------

std::ostream& operator<<(std::ostream& ostr, const Form& form)
{
	for (size_t i = 0; i < form.fieldSize(); i++) //Print form as needed, including errors
	{
		std::cout << "-------------------------------------------------------------------------\n";
		form.getField()[i]->print();
		std::cout << "	";
		if (!form.getField()[i]->getValidity())
			form.getField()[i]->checkFieldError();
		std::cout << std::endl;
		std::cout << "-------------------------------------------------------------------------\n";
	}
	for (size_t i = 0; i < form.numOfValidators(); i++)
		if (!form.getValidator()[i]->validate())
		{
			std::cout << form.getValidator()[i]->errorMessage();
			form.getValidator()[i]->invalidateFields();
			std::cout << std::endl;
			break;
		}
	std::cout << std::endl;
	return ostr;
}