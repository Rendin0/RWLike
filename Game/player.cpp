#include "player.h"

Player::Player()
{
	id = 0;
	name = "RWRW";
	inventory = {};
}

Player::Player(int id, std::string name, int max_hp, int hp, int damage) : Attributes(max_hp, hp, damage)
{
	this->id = id;
	this->name = name;
}

Attributes::Attributes()
{
	max_hp = 0;
	hp = 0;
	damage = 0;
}

Attributes::Attributes(int max_hp, int hp, int damage)
{
	this->max_hp = max_hp;
	this->hp = hp;
	this->damage = damage;
}

Player& Player::takeDamage()
{
	hp--;
	checkState();

	return *this;
}

Player& Player::takeDamage(int value)
{
	hp -= value;
	checkState();

	return *this;
}

Player& Player::die()
{
	printf("You lose");
	return *this;
}

void Player::checkState()
{
	if (hp <= 0)
		die();
}