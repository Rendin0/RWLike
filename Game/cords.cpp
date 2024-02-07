#include "cords.h"

Cords::Cords()
{
	x = 1;
	y = 1;
}

Cords::Cords(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Cords::getX()
{
	return x;
}

int Cords::getY()
{
	return y;
}

Cords& Cords::setX(int x)
{
	this->x = x;
	return *this;
}

Cords& Cords::setY(int y)
{
	this->y = y;
	return *this;
}

Cords Cords::getCords()
{
	return *this;
}

Cords& Cords::setCords(Cords cords)
{
	*this = cords;
	return *this;
}

void setCursorPosition(Cords cords)
{
	std::wcout << L"\u001b[" << cords.getY() << L";" << cords.getX() << L"H";
}
