#pragma once
#include <vector>
#include "BaseField.h"
#include "BaseValidator.h"
#include "ComplexValidator.h"
#include <iostream>

class Form
{
public:
	Form() {} //Constructor
	~Form() {} //Destructor
	void addValidator(BaseValidator<class T> *validator) { m_validator.push_back(validator); } //Add new validator to field
	std::vector<BaseValidator<class T>*> getValidator() const { return m_validator; }; //Get the validator vector
	void addField(BaseField *field) { m_fields.push_back(field); } //Add new field
	std::vector<BaseField *> getField() const { return m_fields; } //Return field
	size_t numOfValidators() const { return m_validator.size(); } //Return number of validators
	size_t fieldSize() const { return m_fields.size(); }; //Return size of field
	bool validateForm(); //Check validity of all fields in the form
	void fillForm(); //Input data to all fields in the form
	
private:
	std::vector<BaseField *>  m_fields; //Vector of all fields
	std::vector<BaseValidator<class T>*> m_validator; //Vector of additional validators
};

std::ostream& operator<<(std::ostream& ostr, const Form& form);

