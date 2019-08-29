//- - - - - - - - include section- - - - - - -
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
class readFromFile
{
public:
	readFromFile() { m_readState = false; } //Constructor
	~readFromFile() {} //Destructor
	bool getReadState() const { return m_readState; } //Return whether a file is currently open
	void getLineFromFile(std::istream& in); //Get a line of text from the file and add it to the input buffer
	void openFile(); //Ask a filename from the user and open a file with that name if possible
	void closeFile(std::istream& in); //Closes the currently open file
	void stopReadingFromFile(std::istream& in); //Restore the input buffer to its default state
	std::string displayCurrentLine() { return m_currentLine; } //Return the latest line read from the file
	void insertString(std::istream& in, std::string input); //Enter a string into the input buffer

private:
	std::istringstream stream;
	std::streambuf* m_backup = std::cin.rdbuf(); //Saves a copy of the cin buffer so it can be restored after done reading from a file
	bool m_readState; //Shows whether a file is currently being read
	std::ifstream m_calcFile; //The file that's currently open
	std::string m_currentLine; //The line that's currently being read
};

