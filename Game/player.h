#pragma once
#include "item.h"
#include "cords.h"
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



class Player : public Attributes, public Cords
{
	wchar_t icon;
	int id;

	std::vector<Item> inventory;

	void checkState();
	void die();
public:
	Player();
	Player(int id, wchar_t icon, int max_hp, int hp, int damage);

	Cords getCords();
	Player& setCords(Cords cords);

	wchar_t getIcon();
	Player& setIcon(wchar_t icon);

	Player& takeDamage();
	Player& takeDamage(int value);

};
