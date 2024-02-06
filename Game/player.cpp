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

int Attributes::getMaxHp()
{
	return max_hp;
}

int Attributes::getHp()
{
	return hp;
}

int Attributes::getDamage()
{
	return damage;
}

Attributes& Attributes::setMaxHp(int max_hp)
{
	this->max_hp = max_hp;
	return *this;
}

Attributes& Attributes::setHp(int hp)
{
	this->hp = hp;
	return *this;
}

Attributes& Attributes::setDamage(int damage)
{
	this->damage = damage;
	return *this;
}

Player& Player::takeDamage()
{
	takeDamage(1);

	return *this;
}

Player& Player::takeDamage(int value)
{
	hp -= value;
	std::wcout << L"\u001b[41m";
	if (!checkState())
	{
		Sleep(200);
		std::wcout << L"\u001b[1D\u001b[0m";
		Sleep(100);
	}

	return *this;
}

Player& Player::printInfo()
{
	setCursorPosition(Cords(1, 1));

	std::wcout << "HP: " << hp << "/" << max_hp;
	setCursorPosition(Cords(1, 2));
	std::wcout << "Damage: " << damage;

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
	setCursorPosition(Cords(55, 1));
	std::wcout << L"You (" << icon << L") lose.\n";
}

bool Player::checkState()
{
	printInfo();
	if (hp <= 0)
	{
		die();
		return 1;
	}
	return 0;
}
