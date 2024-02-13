#include "main.h"

int Item::total_items = 0;
int Attribute::total_attributes = 0;
int Entity::total_enityties = 0;
std::queue<std::function<void()>> FrameHandler::functions_queue;

int main()
{
	system("cls");
	_setmode(_fileno(stdout), _O_U16TEXT);


	hideCursor();

	int top_pos = 5, left_pos = 11, length = 110, width = 26;

	Game g1(top_pos, left_pos, length, width);

	Cords p_cords = { length / 2, width / 2 };

	g1.gameBoxPrint();

	std::thread fh(frameHandler, 30);

	g1.createEntity(p_cords, 0, L'♂', 5, 5, 2);
	g1.createEntity(Cords(80, 18), 1, L'G', 8, 8, 1);
	g1.createEntity(Cords(50, 15), 1, L'♀', 8, 8, -1);
	g1.createEntity(Cords(5, 13), 2, L'·', 8, 8, 1);


	g1.addObject(Cords(50, 8), L'#');
	g1.addObject(Cords(60, 10), L'+');

	g1.givePlayerControls();

	while (true)
		if (_getch() == 27)
			break;

	fh.detach();

	system("cls");

	return 0;
}