#include "Pixel.h"

Pixel::Pixel(unsigned char color)
{
	SetColor(color);
}

//----------------------------------------------------------------------

unsigned char Pixel::GetPixelColor() const
{
	return m_color;
}

//----------------------------------------------------------------------

void Pixel::SetColor(unsigned char newColor)
{
	if (newColor == (unsigned char)219 || newColor == (unsigned char)176) //if black or gray
		m_color = newColor;
	else
		m_color = ' ';
}

//----------------------------------------------------------------------

Pixel::~Pixel()
{
}

//----------------------------------------------------------------------

bool operator==(const Pixel& p1, const Pixel& p2)
{
	return p1.GetPixelColor() == p2.GetPixelColor();
}

//----------------------------------------------------------------------

bool operator!=(const Pixel& p1, const Pixel& p2)
{
	return !(p1 == p2);
}

//----------------------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, const Pixel& p)
{
	stream << p.GetPixelColor();
	return stream;
}

//----------------------------------------------------------------------

Pixel operator|(const Pixel & p1, const Pixel & p2)
{
	return (p1.GetPixelColor() >= p2.GetPixelColor()) ? p1 : p2;
}

//----------------------------------------------------------------------

Pixel& operator|=(Pixel & p1, const Pixel & p2)
{
	return p1 = p1 | p2;
}

//----------------------------------------------------------------------

Pixel operator&(const Pixel & p1, const Pixel & p2)
{
	return (p1.GetPixelColor() < p2.GetPixelColor()) ? p1 : p2;
}

//----------------------------------------------------------------------

Pixel& operator&=(Pixel & p1, const Pixel & p2)
{
	return p1 = p1 & p2;
}
