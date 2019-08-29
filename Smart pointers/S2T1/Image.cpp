#include "Image.h"

Image::Image() : m_dataStructure() { Image(0, 0); }

//----------------------------------------------------------------------

Image::Image(int height, int width) : m_dataStructure(height, width) {}

//----------------------------------------------------------------------

Image::Image(const Image & other) : m_dataStructure(other.m_dataStructure) {}

//----------------------------------------------------------------------

Image::~Image() {}

//----------------------------------------------------------------------

int Image::GetHeight() const
{
	return m_dataStructure.GetHeight();
}

//----------------------------------------------------------------------

int Image::GetWidth() const
{
	return m_dataStructure.GetWidth();
}

//----------------------------------------------------------------------

Pixel& Image::operator()(int row, int col)
{
	return m_dataStructure.GetPixel(row, col);
}

//----------------------------------------------------------------------

const Pixel& Image::operator()(int row, int col) const
{
	return m_dataStructure.GetPixel(row, col);
}

//----------------------------------------------------------------------

Image& Image::operator=(const Image &other)
{
	if (*this != other) //Only change image if both images are different
	{
		int height = other.GetHeight();
		int width = other.GetWidth();

		m_dataStructure.deleteData();
		m_dataStructure.ResizeImage(height, width);
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				m_dataStructure.GetPixel(i, j) = other.m_dataStructure.GetPixel(i, j);
	}
	return *this;
}

//----------------------------------------------------------------------

Image& Image::operator+=(const Image&other)
{

	return *this = *this + other;
}

//----------------------------------------------------------------------

bool operator==(const Image & pic1, const Image & pic2)
{
	if (pic1.GetHeight() == pic2.GetHeight() && pic1.GetWidth() == pic2.GetWidth()) //Only check similarity if images are of equal size
	{
		for (int row = 0; row < pic1.GetHeight(); row++)
		{
			for (int col = 0; col < pic1.GetWidth(); col++)
				if (pic1(row, col) != pic2(row, col))
					return false;
		}
	}
	else
		return false;
	return true;
}

//----------------------------------------------------------------------

bool operator!=(const Image & pic1, const Image & pic2)
{
	return !(pic1 == pic2);
}

//----------------------------------------------------------------------

Image operator+(const Image& pic1, const Image & pic2)
{
	int pic1Height = pic1.GetHeight();
	int pic2Height = pic2.GetHeight();
	int newHeight = pic1Height > pic2Height ? pic1Height : pic2Height;
	int newWidth = pic1.GetWidth() + pic2.GetWidth();
	Image temp(newHeight, newWidth);
	for (int i = 0; i < newHeight; i++)
		for (int j = 0; j < pic1.GetWidth(); j++)
			if (pic1Height < newHeight && i >= pic1Height)
				temp(i, j) = ' ';
			else
			{
				temp(i, j) = pic1(i, j);
			}
	for (int i = 0; i < newHeight; i++)
		for (int j = pic1.GetWidth(); j < newWidth; j++)
			if (pic2Height < newHeight && i >= pic2Height)
				temp(i, j) = ' ';
			else
				temp(i, j) = pic2(i, j - pic1.GetWidth());
	return temp;
}

//----------------------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, const Image& image)
{
	for (int i = 0; i < image.GetHeight(); i++)
	{
		for (int j = 0; j < image.GetWidth(); j++)
			stream << image(i, j);
		stream << std::endl;
	}
	return stream;
}

//----------------------------------------------------------------------

std::istream& operator>>(std::istream& stream, Image& image)
{
	int height, width;
	unsigned char tempChar;
	stream >> height >> width;
	Image tempImage(height, width);
	stream.get();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tempChar = stream.get();
			tempImage(i, j) = Pixel(tempChar);
		}
		stream.get(); //Get rid of line break
	}
	image = tempImage;
	return stream;
}

//----------------------------------------------------------------------

Image operator|(const Image& pic1, const Image& pic2)
{
	int height = pic1.GetHeight() > pic2.GetHeight() ? pic1.GetHeight() : pic2.GetHeight();
	int width = pic1.GetWidth() > pic2.GetWidth() ? pic1.GetWidth() : pic2.GetWidth();
	return comparisonHelp(pic1, pic2, '|', height, width);
}

//----------------------------------------------------------------------

Image& operator|=(Image& pic1, const Image& pic2)
{
	return pic1 = pic1 | pic2;
}

//----------------------------------------------------------------------

Image operator&(const Image& pic1, const Image& pic2)
{
	int height = pic1.GetHeight() < pic2.GetHeight() ? pic1.GetHeight() : pic2.GetHeight();
	int width = pic1.GetWidth() < pic2.GetWidth() ? pic1.GetWidth() : pic2.GetWidth();
	return comparisonHelp(pic1, pic2, '&', height, width);
}

//----------------------------------------------------------------------

Image& operator&=(Image& pic1, const Image& pic2)
{
	return pic1 = pic1 & pic2;
}

//----------------------------------------------------------------------

Image comparisonHelp(const Image& pic1, const Image& pic2, char operation, int height, int width)
{
	Image tempImage(height, width);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (i < pic1.GetHeight() && i < pic2.GetHeight() && j < pic1.GetWidth() && j < pic2.GetWidth()) //Only perform comparison if pixel exists in the specific coordinates in both pictures
				if (operation == '&') //Compare using the appropriate symbol
					tempImage(i, j) = pic1(i, j) & pic2(i, j);
				else
					tempImage(i, j) = pic1(i, j) | pic2(i, j);
			else
				tempImage(i, j) = ' ';
	return tempImage;
}

//----------------------------------------------------------------------

Image operator*(const Image& pic, int n)
{
	int height = pic.GetHeight();
	int width = pic.GetWidth() * n;
	Image tempImage(height, width);
	if (n = 0)
		return tempImage;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			tempImage(i, j) = pic(i, j % pic.GetWidth());
	return tempImage;
}

//----------------------------------------------------------------------

Image operator*(int n, const Image& pic)
{
	return pic * n;
}

//----------------------------------------------------------------------

Image& operator*=(Image& pic, int n)
{
	return pic = pic * n;
}

//----------------------------------------------------------------------

Image& operator++(Image& pic)
{
	int k; //Used for the loop
	Image tempImage(pic.GetHeight(), pic.GetWidth() * 2);
	for (int i = 0; i < pic.GetWidth(); i++)
		for (int j = 0, k = 0; j < pic.GetWidth(); j++, k += 2) //Repeat each row twice
		{
			tempImage(i, k) = pic(i, j);
			tempImage(i, k + 1) = pic(i, j);
		}
	return pic = tempImage;
}

//----------------------------------------------------------------------

Image& operator++(Image& pic, int a)
{
	Image tempImage(pic);
	++pic;
	return tempImage;
}

//----------------------------------------------------------------------

Image& operator--(Image& pic)
{
	int k;
	Image tempImage(pic.GetHeight(), pic.GetWidth() / 2);
	for (int i = 0; i < pic.GetWidth(); i++) //Only print every other row
		for (int j = 0, k = 1; k < pic.GetWidth(); j++, k += 2)
			tempImage(i, j) = pic(i, k);
	return pic = tempImage;
}

//----------------------------------------------------------------------

Image& operator--(Image& pic, int a)
{
	Image tempImage(pic);
	--pic;
	return tempImage;
}