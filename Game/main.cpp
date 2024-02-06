#include "main.h"

int Item::total_items = 0;
int Attribute::total_attributes = 0;

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	hideCursor();

	int top_pos = 5, left_pos = 11, length = 110, width = 26;

	Game g1(top_pos, left_pos, length, width);

	g1.createPlayer(0, L'P', 0, 0, 0);
	g1.gameBoxPrint();

	bool controls = true;

	g1.giveControls(controls);

	return 0;
}