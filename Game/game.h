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

class Game : public GameBox
{
	bool have_controls;
	Player* p1;

	Game& playerCollide(wchar_t obj);

public:
	Game();
	Game(int top_pos, int left_pos, short length, short width);

	Game& addObject(Cords cords, wchar_t obj);
	Game& moveObject(Cords new_cords, Cords old_cords);

	Game& giveControls();
	Game& takeControls();

	Game& createPlayer(Cords cords, int id, wchar_t icon, int max_hp, int hp, int damage);

	Game& movePlayer(wchar_t dir, short amount);

	~Game();
};