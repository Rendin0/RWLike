#include "player.h"
#include <io.h>
#include <fcntl.h>
#include <conio.h>

class GameBox : public Cords
{
protected:
	short length;
	short width;
	std::vector<std::vector<wchar_t>> field;
public:
	GameBox();
	GameBox(int top_pos, int left_pos, short length, short width);

	void gameBoxPrint();
};

void hideCursor();
void setCursorPosition(Cords cords);

class Game : public GameBox
{
	Player* p1;

public:
	Game();
	Game(int top_pos, int left_pos, short length, short width);

	Game& addObject(Cords cords, wchar_t obj);

	Game& giveControls(bool& have_controls);
	Game& takeControls(bool& have_controls);

	Game& createPlayer(Cords cords, int id, wchar_t icon, int max_hp, int hp, int damage);

	Game& movePlayer(wchar_t dir, short amount);

	~Game();
};