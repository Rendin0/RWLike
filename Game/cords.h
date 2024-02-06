#pragma once
class Cords
{

protected:
	int x;
	int y;
public:
	Cords();
	Cords(int x, int y);

	int getX();
	int getY();

	Cords& setX(int x);
	Cords& setY(int y);

	Cords& setCords(int x, int y);
};