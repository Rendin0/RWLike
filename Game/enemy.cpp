#include "enemy.h"

Enemy::Enemy() 
{
}

Enemy::Enemy(wchar_t icon, int max_hp, int hp, int damage) : Entity(1, icon, max_hp, hp, damage)
{
}

Enemy& Enemy::attack(Entity* plr)
{
	if (plr->getType() != 0)
		return *this;

	plr->takeDamage(damage);
	return *this;
}

