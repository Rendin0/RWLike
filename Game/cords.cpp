#include "cords.h"

bool operator==(const Cords& left, const Cords& right)
{
	return left.x == right.x && left.y == right.y;
}

Cords operator+(const Cords& left, const Cords& right)
{
	return Cords(left.x + right.x, left.y + right.y);
}

Cords operator-(const Cords& left, const Cords& right)
{
	return Cords(left.x - right.x, left.y - right.y);
}

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
	return Cords(x, y);
}

Cords& Cords::setCords(Cords cords)
{
	*this = cords;
	return *this;
}

void setCursorPosition(Cords cords)
{
	std::wcout << "\u001b[" << cords.getY() << ";" << cords.getX() << "H";
}

void printQueue(std::wstring str)
{
	FrameHandler::functions_queue.push([=]() {
		std::wcout << str;
		});
}

void printQueue(wchar_t ch)
{
	printQueue(std::wstring(1, ch));
}

void printQueue(std::wstring str, Cords cords)
{
	FrameHandler::functions_queue.push([=]() {
		setCursorPosition(cords);
		std::wcout << str;
		});
}

void printQueue(wchar_t ch, Cords cords)
{
	printQueue(std::wstring(1, ch), cords);
}
