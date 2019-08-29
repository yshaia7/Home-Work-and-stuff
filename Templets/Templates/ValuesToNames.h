#pragma once
#include <iostream>


template <class T>
class ValuesToNames
{
public:
	ValuesToNames() {}; //Constructor
	~ValuesToNames() {}; //Destructor
	void setValue(int n) { m_value = n; } //Set new value from input
	int getValue() { return m_value; } //Return value
	const std::vector<string>& getVector() { return m_vector; } //Get name vector

private:
	int m_value; //User inputted value
	T m_names;
	std::vector<string> m_vector = m_names.getNames(); //Vector of names
};

//-------------------------------------------------------------

template<class T>
std::istream& operator>>(std::istream& is, ValuesToNames<T>& input)
{
	int n;
	is >> n;
	input.setValue(n);
	return is;
}

//-------------------------------------------------------------

template<class T>
std::ostream& operator <<(std::ostream& os, ValuesToNames<T>& input)
{
	if (input.getValue() >= 1 && input.getValue() <= input.getVector().size())
		os << input.getVector()[input.getValue() - 1] << "		";
	else
		os << input.getValue() << "		";
	return os;
}

//-------------------------------------------------------------

template<class T>
bool operator<=(T& parameter, int range)
{
	return parameter.getValue() <= range;
}

//-------------------------------------------------------------

template<class T>
bool operator>=(T& parameter, int range)
{
	return parameter.getValue() >= range;
}