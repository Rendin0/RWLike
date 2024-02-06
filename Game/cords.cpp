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

Cords& Cords::setCords(int x, int y)
{
	this->x = x;
	this->y = y;
	return *this;
}
