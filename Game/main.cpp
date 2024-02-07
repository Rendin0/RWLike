#include "main.h"

int Item::total_items = 0;
int Attribute::total_attributes = 0;
int Entity::total_enityties = 0;

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	hideCursor();

	int top_pos = 5, left_pos = 11, length = 110, width = 26;

	Game g1(top_pos, left_pos, length, width);

	Cords p_cords = { length / 2, width / 2 };

	g1.createEntity(p_cords, 0, L'F', 5, 6, 2);
	g1.gameBoxPrint();

	g1.addObject(Cords(50, 8), L'#');
	g1.addObject(Cords(50, 10), L'·');
	g1.addObject(Cords(60, 10), L'+');

	g1.giveControls();

	while (true)
		if (_getch() == 27)
			break;

	system("cls");

	return 0;
}