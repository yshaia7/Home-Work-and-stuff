//- - - - - - - - - include section - - - - - - -
#include "readFromFile.h"

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
void readFromFile::getLineFromFile(std::istream& in)
{
	if (m_calcFile.eof()) //Read until end of file
	{
		closeFile(in);
		return;
	}
	std::getline(m_calcFile, m_currentLine);
	stream.str(m_currentLine);
	in.rdbuf(stream.rdbuf());
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
void readFromFile::openFile()
{
	std::string fileName;
	std::cout << "Enter filename (and path if needed)\n";
	std::cin >> fileName;
	m_calcFile.open(fileName);
	if (!m_calcFile.is_open())
		throw std::exception("Invalid file name or path.");
	m_readState = true;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
void readFromFile::closeFile(std::istream& in)
{
	stopReadingFromFile(in);
	m_readState = false;
	m_calcFile.close();
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
void readFromFile::stopReadingFromFile(std::istream& in)
{
	in.rdbuf(m_backup); //Restore buffer to original state
	in.clear();
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clear the input buffer from any leftover text from the file
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
void readFromFile::insertString(std::istream& in, std::string input)
{
	stream.str(input);
	in.rdbuf(stream.rdbuf());
}