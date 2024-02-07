#include "projectile.h"

Projectile::Projectile()
{
	dirrection = L'0';
}

Projectile::Projectile(wchar_t dirrection, wchar_t icon, int damage) : Entity(2, icon, 99999, 99999, damage)
{
	this->dirrection = dirrection;
}

Projectile& Projectile::attack(Entity* ent)
{
	ent->takeDamage(damage);
	die();
	return *this;
}

void Projectile::die()
{
	// TODO
}
