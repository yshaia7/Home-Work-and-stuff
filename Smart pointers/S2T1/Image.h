#pragma once
#include "ImageDataStructure.h"
#include "Pixel.h"

class Image
{
public:
	Image(); //Default constructor
	Image(int height, int width); //Constructor based on parameters
	Image(const Image& other); //Copy constructor
	int GetHeight() const; //Return current height
	int GetWidth() const; //Return current width
	Pixel& operator()(int row, int col); //Returns specific pixel
	const Pixel& operator()(int row, int col) const; //Returns const pixel
	Image& operator=(const Image &other); //Copy other image to current one
	Image& operator+=(const Image &other);
	~Image(); //Destructor


private:
	ImageDataStructure m_dataStructure;
};

bool operator==(const Image& pic1, const Image& pic2); //Returns true if both pictures are of identical size and contain identical pixels
bool operator!=(const Image& pic1, const Image& pic2);
Image operator+(const Image& pic1, const Image& pic2); //Connect two pictures together
std::ostream& operator<<(std::ostream& stream, const Image& image); //Write pixels to stream
std::istream& operator>>(std::istream& stream, Image& image); //Get pixels from stream
Image operator|(const Image& pic1, const Image& pic2); //Compare pixels and change to the darker ones
Image& operator|=(Image& pic1, const Image& pic2);
Image operator&(const Image& pic1, const Image& pic2); //Compare pixels and change to the lighter ones
Image& operator&=(Image& pic1, const Image& pic2);
Image comparisonHelp(const Image& pic1, const Image& pic2, char operation, int height, int width); //Helps with the & and | operators
Image operator*(const Image& pic, int n); //Return the image being repeated n times
Image operator*(int n, const Image& pic);
Image& operator*=(Image& pic, int n);
Image& operator++(Image& pic); //Return the image with each row being repeated twice
Image& operator++(Image& pic, int);
Image& operator--(Image& pic); //Return the image with every other row being removed, starting with the first row
Image& operator--(Image& pic, int);