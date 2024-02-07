#pragma once
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
};

void setCursorPosition(Cords cords);
