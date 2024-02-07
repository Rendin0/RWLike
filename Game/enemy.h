#include "entity.h"
#include <string>

class Enemy : public Entity
{

public:
	Enemy();
	Enemy(wchar_t icon, int max_hp, int hp, int damage);

	Enemy& attack(Entity* plr) override;
};