#pragma once
#include "item.h"
#include <iostream>

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
	std::string name;

	int id;

	std::vector<Item> inventory;

	void checkState();
	void die();
public:
	Player();
	Player(int id, std::string name, int max_hp, int hp, int damage);

	Player& takeDamage();
	Player& takeDamage(int value);
};
