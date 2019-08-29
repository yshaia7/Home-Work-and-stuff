//- - - - - - - - - include section- - - - - - - - -
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "readFromFile.h"

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
class CalculatorItem;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
class Calculator
{
public:
	Calculator() = default;
	~Calculator() = default;
	void run();
	std::shared_ptr<CalculatorItem> operator[](int index) const;
private:
	int m_maxShapes = -1; //The maximum number of shapes allowed
	readFromFile m_readFile; //Helps us read info from the file and input it into the calculator
	std::vector<std::shared_ptr<CalculatorItem>> m_calculatorItems;
	static std::string getUserCommand();
	static void exit();
	static void help(); 
	void calculateArea();
	void calculatePerimeter();
	void drawItem();
	void findAllSameShapes() const;
	void deleteItem();
	void findMin();
	void findMax();
	void resize();
	void newMaxSize();
	void same(int index) const;
	void createShape();
	void printItemList() const;
	void checkBufferEmpty() const; //Checks if the input buffer is empty when reading lines from the file
	void checkNumOfBufferedInput(int needed); //Check if the input buffer has enough different inputs in one line to execute a command
};

