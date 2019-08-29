#pragma once
class Pixel;

class ImageDataStructure
{
public:
	ImageDataStructure(int height = 0, int width = 0); //Constructor
	ImageDataStructure(const ImageDataStructure & other); //Copy constructor
	~ImageDataStructure(); //Default destructor
	void ResizeImage(int height, int width); //Change image size to new parameters
	int GetHeight() const; //Return current height
	int GetWidth() const; //Return current width
	Pixel& GetPixel(int row, int col) const; //Return pixel based on parameters
	void deleteData(); //Delete all current pixel data and free memory

private:
	int m_height; //Image height
	int m_width; //Image width
	Pixel **m_image; //Image's pixels



};

