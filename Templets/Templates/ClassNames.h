#pragma once
#include <vector>

class ClassNames
{
public:
	ClassNames() {} //Constructor
	~ClassNames() {} //Destructor
	const std::vector<std::string> & getNames() { return m_classes; } //Return vector of classes

private:
	std::vector<std::string> m_classes = { "First Class","Business Class","Economy Class" }; //Vector of class names
};

