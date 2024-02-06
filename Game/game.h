#include "player.h"
#include <io.h>
#include <fcntl.h>
#include <conio.h>

class GameBox
{
protected:
	COORD cords;
	int length;
	int width;
	std::vector<std::vector<wchar_t>> field;
public:
	GameBox();
	GameBox(int top_pos, int left_pos, int length, int width);

	void gameBoxPrint();
};

void hideCursor();
void setCursorPosition(COORD cords);

class Game : public GameBox
{
	Player* p1;

public:
	Game();
	Game(int top_pos, int left_pos, int length, int width);

	Game& giveControls(bool& have_controls);
	Game& takeControls(bool& have_controls);

	Game& createPlayer(int id, wchar_t icon, int max_hp, int hp, int damage);

	Game& movePlayer(wchar_t dir, short amount);

	~Game();
};