#include "player.h"
#include <cwchar>
#include <windows.h>

class GameBox
{
	int top_pos;
	int left_pos;
	int length;
	int width;
public:
	GameBox();
	GameBox(int top_pos, int left_pos, int length, int width);

	void gameBoxPrint();
	void movePlayer(char player, int amount, char dir);
};


void hideCursor();

void setCursorPosition(int top_pos, int left_pos);