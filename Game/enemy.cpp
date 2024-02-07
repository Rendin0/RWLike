#include "enemy.h"

Enemy::Enemy() 
{
	walking = shooting = false;
}

Enemy::Enemy(wchar_t icon, int max_hp, int hp, int damage) : Entity(1, icon, max_hp, hp, damage)
{
	walking = shooting = false;
}

Enemy& Enemy::setShooting(bool state)
{
	shooting = state;
	return *this;
}

Enemy& Enemy::setWalking(bool state)
{
	walking = state;
	return *this;
}

bool Enemy::getShooting()
{
	return shooting;
}

bool Enemy::getWalking()
{
	return walking;
}

Enemy& Enemy::attack(Entity* plr)
{
	if (plr->getType() != 0)
		return *this;

	plr->takeDamage(damage);
	return *this;
}

