#include "player.h"
#include <cwchar>
#include <windows.h>

class GameBox
{
	COORD cords;
	COORD player_cords;
	int length;
	int width;
public:
	GameBox();
	GameBox(int top_pos, int left_pos, int length, int width);

	void gameBoxPrint();
	void movePlayer(char player, int amount, char dir, int dir_int, int dir_mod);

	GameBox& setPlayerPosition(COORD cords);
	COORD getPlayerCords();
};


void hideCursor();

void setCursorPosition(COORD cords);