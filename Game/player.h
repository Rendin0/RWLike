#pragma once
#include "item.h"
#include <iostream>
#include <windows.h>


class Attributes
{

protected:
	int max_hp;
	int hp;
	int damage;

	Attributes();
	Attributes(int max_hp, int hp, int damage);
public:
	
};

class Player : public Attributes
{
	wchar_t icon;
	int id;
	COORD player_cords;

	std::vector<Item> inventory;

	void checkState();
	void die();
public:
	Player();
	Player(int id, wchar_t icon, int max_hp, int hp, int damage);

	COORD getCords();
	Player& setCords(COORD cords);

	wchar_t getIcon();
	Player& setIcon(wchar_t icon);

	Player& takeDamage();
	Player& takeDamage(int value);

};
