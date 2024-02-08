#pragma once
#include "entity.h"
#include "cords.h"

class Projectile : public Entity
{
	wchar_t dirrection;
public:
	Projectile();
	Projectile(wchar_t dirrection, wchar_t icon, int damage);

	Projectile& attack(Entity* ent) override;

	wchar_t getDirrection();

	void die() override;  //TODO
};