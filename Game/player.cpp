#include "player.h"

Player::Player()
{
	icon = L'P';
	inventory = {};
}

Player::Player(wchar_t icon, int max_hp, int hp, int damage) : Entity(0, icon, max_hp, hp, damage)
{
	inventory = {};
}

Player& Player::takeDamage()
{
	return takeDamage(1);
}

Player& Player::heal(int value)
{
	if (hp + value > max_hp)
		return *this;
	hp += value;

	std::wcout << L"\u001b[42m";
	printInfo();
	Sleep(200);
	std::wcout << L"\u001b[1D\u001b[0m";
	Sleep(100);
	printInfo();

	return *this;
}

Player& Player::heal()
{
	return heal(1);
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

Player& Player::die()
{
	setCursorPosition(Cords(55, 1));
	std::wcout << L"You (" << icon << L") lose.";
	setCursorPosition(Cords(56, 2));
	std::wcout << L"Esc to exit";
	return *this;
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
