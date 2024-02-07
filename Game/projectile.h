#pragma once
#include "entity.h"
#include "cords.h"

class Projectile : public Entity, public Cords
{
	wchar_t dirrection;
public:
	Projectile();
	Projectile(wchar_t dirrection, wchar_t icon, int damage);

	Projectile& attack(Entity* ent) override;
	void die() override;  //TODO
};