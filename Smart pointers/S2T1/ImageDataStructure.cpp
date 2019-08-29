#include "ImageDataStructure.h"
#include "Pixel.h"

ImageDataStructure::ImageDataStructure(int height, int width)
{
	ResizeImage(height, width);
}

//----------------------------------------------------------------------

ImageDataStructure::ImageDataStructure(const ImageDataStructure& other)
{
	ResizeImage(other.GetHeight(), other.GetWidth());
	for (int i = 0; i < m_height; i++)
		for (int j = 0; j < m_width; j++)
			m_image[i][j] = other.GetPixel(i, j);
}

//----------------------------------------------------------------------

void ImageDataStructure::ResizeImage(int height, int width)
{
	if (height == 0 || width == 0)
	{
		m_image = nullptr;
		return;
	}
	m_height = height;
	m_width = width;
	m_image = new Pixel*[height];

	for (int i = 0; i < height; i++)
		m_image[i] = new Pixel[width];
}

//----------------------------------------------------------------------

Pixel& ImageDataStructure::GetPixel(int row, int col) const
{
	return m_image[row][col];
}

//----------------------------------------------------------------------

int ImageDataStructure::GetHeight() const
{
	return m_height;
}

//----------------------------------------------------------------------

int ImageDataStructure::GetWidth() const
{
	return m_width;
}

//----------------------------------------------------------------------

ImageDataStructure::~ImageDataStructure()
{
	deleteData();
}

//----------------------------------------------------------------------

void ImageDataStructure::deleteData()
{
	for (int i = 0; i < m_height; i++)
		delete[] m_image[i];
	delete[] m_image;
}