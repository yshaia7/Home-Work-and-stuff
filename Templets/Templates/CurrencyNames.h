#pragma once
#include <vector>


class CurrencyNames
{
public:
	CurrencyNames() {} //Constructor
	~CurrencyNames() {} //Destructor
	std::vector<std::string> getNames() { return m_currencies; } //Return vector of currencies

private:
	std::vector<std::string> m_currencies = { "NIS","Euro","Dollar" }; //Vector of currency names
};

