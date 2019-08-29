#pragma once
#include <vector>

class DestinationNames
{
public:
	DestinationNames() {} //Constructor
	~DestinationNames() {} //Destructor
	std::vector<std::string> getNames() { return m_destinations; } //Return vector of destinations

private:
	std::vector<std::string> m_destinations = { "Rome","Prague","New York","India","Thailand" }; //Vector of destination names
};

