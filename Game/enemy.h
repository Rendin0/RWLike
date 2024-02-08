#include "entity.h"
#include "cords.h"
#include <string>

class Enemy : public Entity
{
	bool shooting;
	bool walking;

public:
	Enemy();
	Enemy(wchar_t icon, int max_hp, int hp, int damage);

	Enemy& setShooting(bool state);
	Enemy& setWalking(bool state);

	bool getShooting();
	bool getWalking();

	Enemy& attack(Entity* plr) override;
};