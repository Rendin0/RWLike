#include "player.h"

Player::Player()
{
	id = 0;
	icon = L'P';
	inventory = {};
	player_cords.X = 1;
	player_cords.Y = 1;
}

Player::Player(int id, wchar_t icon, int max_hp, int hp, int damage) : Attributes(max_hp, hp, damage)
{
	this->id = id;
	this->icon = icon;
	player_cords.X = 1;
	player_cords.Y = 1;
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

COORD Player::getCords()
{
	return player_cords;
}

Player& Player::setCords(COORD cords)
{
	player_cords = cords;
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