#include "main.h"

int Item::total_items = 0;
int Attribute::total_attributes = 0;

int main()
{
	system("chcp 1251");
	hideCursor();
	system("cls");

	int top_pos = 8, left_pos = 20, length = 96, width = 20;

	gameBoxPrint(top_pos, left_pos, length, width);
	setCursorPosition(top_pos + (width / 2), left_pos + (length / 2));
	std::cout << 'P';

	while (true)
	{
		if (_kbhit())
		{
			_getch();
			int dir_int = _getch();
			char dir = 'A';

			switch (dir_int)
			{
			case 72:
				Sleep(50);
				dir = 'A';
				break;
			case 75:
				dir = 'D';
				break;
			case 77:
				dir = 'C';
				break;
			case 80:
				Sleep(50);
				dir = 'B';
				break;
			default:
				break;
			}


			movePlayer('P', 1, dir);

		}
	}

	//Player p1(0, "Good man", 3, 3, 5);

	return 0;
}