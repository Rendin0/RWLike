#include "player.h"

Player::Player()
{
	id = 0;
	icon = L'P';
	inventory = {};
}

Player::Player(int id, wchar_t icon, int max_hp, int hp, int damage) : Attributes(max_hp, hp, damage)
{
	this->id = id;
	this->icon = icon;
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
	std::cout << "Ouch!\n";
	checkState();

	return *this;
}

Player& Player::takeDamage(int value)
{
	hp -= value;
	std::cout << "Ouch!\n";
	checkState();

	return *this;
}

Cords Player::getCords()
{
	return Cords(x, y);
}

Player& Player::setCords(Cords cords)
{
	x = cords.getX();
	y = cords.getY();
	return *this;
}

wchar_t Player::getIcon()
{
	return icon;
}

Player& Player::setIcon(wchar_t icon)
{
	this->icon = icon;
	return *this;
}

void Player::die()
{
	std::wcout << icon << " lose.\n";
}

void Player::checkState()
{
	if (hp <= 0)
		die();
}
