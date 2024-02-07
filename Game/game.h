#include "player.h"
#include "enemy.h"
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
	bool player_have_controls;
	Player* p1;
	std::vector<Enemy> enemies;

	Game& playerCollide(wchar_t obj, Cords cords);
	Game& playerCollide(Entity* ent);

public:
	Game();
	Game(int top_pos, int left_pos, short length, short width);

	Game& addObject(Cords cords, wchar_t obj);
	Game& moveObject(Cords new_cords, Cords old_cords);

	Game& givePlayerControls();
	Game& takeControls();

	Game& createEntity(Cords cords, int type, wchar_t icon, int max_hp, int hp, int damage); // Types: 0(Player), 1(enemy), 2(projectyle), 3(misc)
	Game& initEntity(Cords cords, Entity* ent);

	Game& movePlayer(wchar_t dir, short amount);

	~Game();
};