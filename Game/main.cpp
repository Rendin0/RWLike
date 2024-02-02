#include "main.h"

int Item::total_items = 0;
int Attribute::total_attributes = 0;

int main()
{
	system("chcp 1251");
	hideCursor();
	system("cls");

	int top_pos = 8, left_pos = 20, length = 96, width = 20;

	GameBox gb(top_pos, left_pos, length, width);

	COORD p_pos;
	p_pos.X = top_pos + width / 2;
	p_pos.Y = left_pos + length / 2;
	gb.setPlayerPosition(p_pos);



	gb.gameBoxPrint();
	setCursorPosition(gb.getPlayerCords());
	std::cout << 'P';

	while (true)
	{
		if (_kbhit())
		{
			_getch();
			int dir_int = _getch(), dir_mod;
			char dir = 'A';

			switch (dir_int)
			{
			case 72:
				Sleep(50);
				dir_int = 0;
				dir_mod = -1;
				dir = 'A';
				break;
			case 75:
				dir = 'D';
				dir_int = 1;
				dir_mod = -1;
				break;
			case 77:
				dir_int = 1;
				dir_mod = 1;
				dir = 'C';
				break;
			case 80:
				dir_int = 0;
				dir_mod = 1;
				Sleep(50);
				dir = 'B';
				break;
			default:
				break;
			}


			gb.movePlayer('P', 1, dir, dir_int, dir_mod);

		}
	}

	//Player p1(0, "Good man", 3, 3, 5);

	return 0;
}