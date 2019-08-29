//- - - - - - - - - - - - -include section- - - - - - - - - - - - - -
#include "CalculatorItem.h"
#include "Calculator.h"
#include "Add.h"
#include "Subtraction.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Multiply.h"
#include "Utils.h"
#include <iostream>

//- - - - - - - - - - - - - - using section - - - - - - - - - - - -
using std::cout;
using std::cin;
using std::endl;
using std::string;

//- - - - - - - - - - - - - - - function section - - - - - - - - - - - -
void addShapeCheck(int, int);

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
string Calculator::getUserCommand()
{
	string act;
	cout << endl << "Please enter a command (\"help\" for command list):" << endl;
	cin >> act;
	return act;
}

void Calculator::exit()
{
	cout << "Goodbye.";
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
void Calculator::calculateArea()
{
	checkBufferEmpty();
	const int index = Utils::readInt(std::cin);
	if (index >= m_calculatorItems.size() || index < 0)
		throw std::exception("Invalid index.");
	cout << "Area ";
	m_calculatorItems[index]->printDetails();
	cout << " = " << m_calculatorItems[index]->area() << endl;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
void Calculator::calculatePerimeter()
{
	checkBufferEmpty();
	const int index = Utils::readInt(std::cin);
	if (index >= m_calculatorItems.size() || index < 0)
		throw std::exception("Invalid index.");
	cout << "Perimeter ";
	m_calculatorItems[index]->printDetails();
	cout << " = " << m_calculatorItems[index]->perimeter() << endl;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
void Calculator::drawItem()
{
	checkBufferEmpty();
	const int index = Utils::readInt(std::cin);
	if (index < 0 || index >= m_calculatorItems.size())
		throw std::exception("Invalid index.");
	m_calculatorItems[index]->draw();
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
void Calculator::findAllSameShapes() const
{
	checkBufferEmpty();
	const int index = Utils::readInt(std::cin);
	if (index < 0 || index >= m_calculatorItems.size())
		throw std::exception("Invalid index.");
	same(index);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
void Calculator::deleteItem()
{
	checkBufferEmpty();
	const int index = Utils::readInt(std::cin);
	if (index < 0 || index >= m_calculatorItems.size())
		throw std::exception("Invalid index.");
	m_calculatorItems.erase(m_calculatorItems.begin() + index);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
void Calculator::findMin()
{
	checkBufferEmpty();
	const int amount = Utils::readInt(std::cin);
	checkNumOfBufferedInput(amount);
	if (amount > m_calculatorItems.size())
		throw std::exception("Invalid amount. Amount can't be larger than total number of shapes.");
	//in first time (for Comparison)
	int index = Utils::readInt(std::cin);
	if (index < 0 || index >= m_calculatorItems.size())
		throw std::exception("Invalid index.");
	double min = m_calculatorItems[index]->area();

	for (int i = 0; i < amount - 1; i++)
	{
		index = Utils::readInt(std::cin);
		if (index < 0 || index >= m_calculatorItems.size())
			throw std::exception("Invalid index.");
		min = m_calculatorItems[index]->area() < min ? m_calculatorItems[index]->area() : min;
	}
	cout << "The minimum area is:" << min << endl;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
void Calculator::findMax()
{
	checkBufferEmpty();
	const int amount = Utils::readInt(std::cin);
	checkNumOfBufferedInput(amount);
	if (amount > m_calculatorItems.size())
		throw std::exception("Invalid amount. Amount can't be larger than total number of shapes.");
	//Calculates the largest area of all selected shapes, return the index of the maxim
	double max = 0;
	for (int i = 0; i < amount; i++)
	{
		const int index = Utils::readInt(std::cin);
		if (index < 0 || index >= m_calculatorItems.size())
			throw std::exception("Invalid index.");
		max = m_calculatorItems[index]->area() > max ? m_calculatorItems[index]->area() : max;
	}
	cout << "The maximum area is:" << max << endl;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
//Change the maximum number of allowed shapes, this time the user can choose more than 100
void Calculator::resize()
{
	while (true)
	{
		checkBufferEmpty();
		char input;
		cout << "Enter new maximum size: ";
		int newMax = Utils::readInt(std::cin);
		if (newMax <= 0)
			throw std::exception("Invalid input. Size must be larger than 0");
		if (newMax < m_calculatorItems.size())
		{
			cout << "New size is smaller than the current number of items.\nEnter 'y' to shrink the list anyway, or 'n' to enter a new number.\n";
			cin >> input;
			if (input == 'n')
				continue;
			else if (input == 'y')
			{
				m_calculatorItems.resize(newMax);
				m_maxShapes = newMax;
				break;
			}
			else
				throw std::exception("Invalid input.");
		}
		m_maxShapes = newMax;
		break;
	}

}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
//Choose the maximum allowed number of shapes during startup (up to 100)
void Calculator::newMaxSize()
{
	cout << "Enter the maximum number of shapes used (1 - 100): ";
	m_maxShapes = Utils::readInt(std::cin);
	if (m_maxShapes <= 0 || m_maxShapes > 100)
		throw std::exception("Invalid input. Enter a number between 1 and 100\n");
}

//the main function in this class, performs actions at user request
void Calculator::run()
{
	//Enter max number of shapes allowed
	while (true)
	{
		try
		{
			newMaxSize();
			break;
		}
		catch (std::exception& inputException)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << inputException.what() << "\n";
		}
	}

	//Enter commands
	while (true)
	{
		try
		{
			printItemList();
			//Get user input from a file if needed
			if (m_readFile.getReadState())
				m_readFile.getLineFromFile(cin);
			//the user request is in the form of string
			auto command = getUserCommand();
			//exit from the calculator
			if (command == "exit")
			{
				exit();
				return;
			}
			//request for the list of option to action(-to requests)
			if (command == "help")
			{
				help();
				continue;
			}
			//create a basic shape and put it in the calculator
			if (command == "cre")
			{
				addShapeCheck(m_maxShapes, m_calculatorItems.size());
				createShape();
				continue;
			}
			//calculate the area of a shape from the calculator, the shape is requested by number(-index)
			if (command == "area")
			{
				calculateArea();
				continue;
			}
			//calculate the perimeter of a shape from the calculator, the shape is requested by number(-index)
			if (command == "per")
			{
				calculatePerimeter();
				continue;
			}
			//create a new shape that consist of multiple of one shape, and put it in the calculator
			if (command == "mul")
			{
				addShapeCheck(m_maxShapes, m_calculatorItems.size());
				if (m_readFile.getReadState())
					checkNumOfBufferedInput(2);
				m_calculatorItems.push_back(std::make_shared<Multiply>(std::cin, *this));
				continue;
			}
			//create a new shape that consist of add of one shape and another shape, and put it in the calculator
			if (command == "add")
			{
				addShapeCheck(m_maxShapes, m_calculatorItems.size());
				if (m_readFile.getReadState())
					checkNumOfBufferedInput(2);
				m_calculatorItems.push_back(std::make_shared<Add>(std::cin, *this));
				continue;
			}
			//create a new shape that consist of subtraction of one shape from another shape, and put it in the calculator
			if (command == "sub")
			{
				addShapeCheck(m_maxShapes, m_calculatorItems.size());
				if (m_readFile.getReadState())
					checkNumOfBufferedInput(2);
				m_calculatorItems.push_back(std::make_shared<Subtraction>(std::cin, *this));
				continue;
			}
			//Draws the shape (regardless of its actual size)
			if (command == "draw")
			{
				drawItem();
				continue;
			}
			//Prints all indexes of the shapes that are equal in their area and perimeter to the selected shape
			if (command == "same")
			{
				findAllSameShapes();
				continue;
			}
			//Deletes the required shape from the calculator and arranges the indexes of the other shapes
			if (command == "del")
			{
				deleteItem();
				continue;
			}
			//Finds and prints the largest of the shapes in the calculator, according to the user selection
			if (command == "min")
			{
				findMin();
				continue;
			}
			//Finds and prints the smallest of the shapes in the calculator, according to the user selection
			if (command == "max")
			{
				findMax();
				continue;
			}
			else if (command == "resize")
			{
				resize();
				continue;
			}
			else if (command == "read")
			{
				m_readFile.openFile();
				continue;
			}
			else
				throw std::exception("Invalid input.");
		}
		//Print an error message if received an invalid input, and show additional information if the error came from a file
		catch (std::exception& calcException)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << calcException.what() << "\n";
			if (m_readFile.getReadState())
			{
				string exceptionCommand;
				cout << "An error has occured while reading from file.\n" << "The incorrect line is: " << m_readFile.displayCurrentLine() << "\n" <<
															  "Enter 'y' to continue reading from file or another character to read normal input\n";
				m_readFile.stopReadingFromFile(cin);
				cin >> exceptionCommand;
				if (exceptionCommand != "y")
					m_readFile.closeFile(cin);
			}
		}
	}
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
std::shared_ptr<CalculatorItem> Calculator::operator[](int index) const
{
	if (index < 0 || index >= m_calculatorItems.size())
		throw std::exception("Invalid index.");
	return m_calculatorItems[index];
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
//Checks if the input buffer is empty when reading lines from the file
void Calculator::checkBufferEmpty() const
{
	if (m_readFile.getReadState() && cin.eof())
		throw std::exception("Not enough data in text line.");
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - -
//Check if the input buffer has enough different inputs in one line to execute a command
void Calculator::checkNumOfBufferedInput(int needed)
{
	bool returnFlag = false;
	string temp = "";
	string received;
	int numOfInputs = 0;
	while (!cin.eof())
	{
		cin >> received;
		temp += received;
		temp += " ";
		numOfInputs++;
		if (numOfInputs >= needed)
		{
			returnFlag = true;
			break;
		}
	}
	m_readFile.insertString(cin, temp);
	if (!returnFlag)
		throw std::exception("Not enough data in file's line for the whole command");
}

//--------------------------------------------------------
//Prints a help screen with a list of possible commands and a brief explanation of it
void Calculator::help()
{
	cout << "Following is the list of the calculator's available commands" << endl
		<< "cre(ate) #shape <R - rectangle | T-triangle | C- circle>" << endl
		<< "area num - Computes the area of shape #num" << endl
		<< "per(imeter) num - Computes the perimeter of shape #num" << endl
		<< "draw num - Draw the shape" << endl
		<< "#num mul(tiply) num x - Creates an item that is the multiplication of shape #num x times" << endl
		<< "add num1 num2 - Creates an item that is the sum of item #num1 and function #num2" << endl
		<< "sub num1 num2 - Creates an item that is the subtraction of item #num1 and function #num2" << endl
		<< "min n #num1-#numN - Returns the smallest area in the chosen shapes. n - the requested shapes: #num1..." << endl
		<< "max n #num1-#numN - Returns the biggest area in the chosen shapes. n - the requested shapes: #num1..." << endl
		<< "same num - Returns shapes with which have the same area and perimeter to the shape #num" << endl
		<< "del(ete) num - Deletes item #num from function list" << endl
		<< "help - Prints this help screen" << endl
		<< "exit - Exits the program." << endl;
}

//--------------------------------------------------------
//Prints all indices of the shapes that are equal in their area and scope to the selected shape
void Calculator::same(int index) const
{
	const double area = m_calculatorItems[index]->area();
	const double perimeter = m_calculatorItems[index]->perimeter();
	
	for (auto i = 0; i < m_calculatorItems.size(); ++i)
	{
		if (m_calculatorItems[i]->area() == area 
			&& m_calculatorItems[i]->perimeter() == perimeter
			&& i != index)
		{
			cout << i << ": ";
			m_calculatorItems[i]->printDetails();
			cout << endl;
		}
	}
	cout << endl;
}


//-----------------------------------------------------------
//Create a new shape and add it to the list
void Calculator::createShape()
{
	char shape;
	checkBufferEmpty();
	cin >> shape;
	shape = toupper(shape);

	if (shape == 'R')
	{
		if (m_readFile.getReadState())
			checkNumOfBufferedInput(2);
		m_calculatorItems.push_back(std::make_shared<Rectangle>(std::cin));
	}
	else if (shape == 'C')
	{
		if (m_readFile.getReadState())
			checkNumOfBufferedInput(1);
		m_calculatorItems.push_back(std::make_shared<Circle>(std::cin));
	}
	else if (shape == 'T')
	{
		if (m_readFile.getReadState())
			checkNumOfBufferedInput(2);
		m_calculatorItems.push_back(std::make_shared<Triangle>(std::cin));
	}
	else
		throw std::exception("Invalid shape type. The Valid options are R, C or T.");
}

//-----------------------------------------------------------
//Prints all the shapes created by the user and the maximum number of shapes allowed
void Calculator::printItemList() const
{
	int i = 0;
	cout << "\nThis is the shapes list:" << endl;
	for (auto& item : m_calculatorItems)
	{
		cout << i++ << ": ";
		item->printDetails();
		cout << endl;
	}
	cout << "The max amount of shapes in the list is " << m_maxShapes << endl;
}

//-----------------------------------------------------------
//Check if another shape can be added, and send an exception if not
void addShapeCheck(int maxLength, int currentLength)
{
	if (currentLength >= maxLength)
		throw std::exception("Cannot add any more shapes");
}