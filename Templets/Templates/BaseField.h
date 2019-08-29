#pragma once


using std::string;
class BaseField
{
public:
	BaseField(string inputQuestion) : m_inputQuestion(inputQuestion) {} //Constructor
	virtual ~BaseField() {} //Destructor
	virtual void input() = 0; //Input to the field
	virtual void print() = 0; //Print field contents
	virtual void checkFieldError() = 0; //Check if the field is valid, and print error message if not
	bool getValidity() { return m_validity; } //Return whether the field is valid
	const string & getQuestion() const { return m_inputQuestion; } //Print the appropriate question for input by user

protected:
	const string m_inputQuestion; //Question asked by user for input of a specific field
	bool m_validity = false; //Current field validity
};

