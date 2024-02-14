#pragma once
#include "frame.h"
#include <string>
#include <iostream>

class Cords
{

protected:
	int x;
	int y;
public:
	Cords();
	Cords(int x, int y);

	virtual int getX();
	virtual int getY();

	virtual Cords& setX(int x);
	virtual Cords& setY(int y);

	virtual Cords getCords();
	virtual Cords& setCords(Cords cords);

	friend bool operator==(const Cords& left, const Cords& right);
	friend Cords operator+(const Cords& left, const Cords& right);
	friend Cords operator-(const Cords& left, const Cords& right);
};

void setCursorPosition(Cords cords);

void printQueue(const std::wstring str);
void printQueue(const wchar_t ch);
void printQueue(const std::wstring str, Cords cords);
void printQueue(const wchar_t ch, Cords cords);
