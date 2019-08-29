#pragma once
#include <iostream>

class Pixel
{
public:
	Pixel(unsigned char color = ' '); //Constuctor
	unsigned char GetPixelColor() const; //Return pixel's current color
	void SetColor(unsigned char newColor); //Change pixel color
	~Pixel(); //Default destructor

private:
	unsigned char m_color; //The pixel's current color
};

bool operator==(const Pixel &p1, const Pixel &p2); //Compare pixel colors
bool operator!=(const Pixel &p1, const Pixel &p2);
std::ostream & operator<<(std::ostream &os, const Pixel &p);
Pixel operator|(const Pixel &p1, const Pixel &p2); //Return the darker pixel
Pixel& operator|=(Pixel &p1, const Pixel &p2);
Pixel operator&(const Pixel &p1, const Pixel &p2); //Return the lighter pixel
Pixel& operator&=(Pixel &p1, const Pixel &p2);






