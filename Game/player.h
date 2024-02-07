#pragma once
#include "item.h"
#include "cords.h"
#include <windows.h>
#include "entity.h"

class Player : public Entity, public Cords
{
	std::vector<Item> inventory;

public:
	bool checkState() override;
	Player();
	Player(wchar_t icon, int max_hp, int hp, int damage);

	Player& die() override;

	Player& takeDamage(int value) override;
	Player& takeDamage() override;

	Player& heal(int value) override;
	Player& heal() override;

	Player& printInfo();
};
