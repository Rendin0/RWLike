#include "main.h"

int Item::total_items = 0;
int Attribute::total_attributes = 0;

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	hideCursor();

	int top_pos = 5, left_pos = 11, length = 110, width = 26;

	Game g1(top_pos, left_pos, length, width);

	Cords p_cords = {length / 2, width / 2};

	g1.createPlayer(p_cords, 0, L'P', 0, 0, 0);
	g1.gameBoxPrint();

	g1.addObject(Cords(5, 5), L'+');

	bool controls = true;

	g1.giveControls(controls);

	return 0;
}