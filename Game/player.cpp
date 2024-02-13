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
	if (hp > max_hp)
		return *this;
	if (hp + value > max_hp)
	{
		hp = max_hp;
		return *this;
	}

	hp += value;

	/*FrameHandler::functions_queue.push([&] {
		std::wcout << L"\u001b[42m";
		});
	printInfo();
	Sleep(200);
	FrameHandler::functions_queue.push([&] {
		std::wcout << L"\u001b[1D\u001b[0m";
		});
	Sleep(100);*/
	printInfo();

	return *this;
}

Player& Player::heal()
{
	return heal(1);
}

Player& Player::takeDamage(int value)
{
	if (value < 0)
		return heal(abs(value));

	hp -= value;
	if (!checkState())
	{
		/*FrameHandler::functions_queue.push([&] {
			std::wcout << L"\u001b[41m";
			Sleep(200);
			std::wcout << L"\u001b[1D\u001b[0m";
			Sleep(100);
			});*/
	}

	return *this;
}

Player& Player::printInfo()
{
	printQueue(std::wstring(L"HP: " + std::to_wstring(hp) + L"/" + std::to_wstring(max_hp)), Cords(1, 1));
	printQueue(std::wstring(L"Damage: " + std::to_wstring(damage)), Cords(1, 2));

	return *this;
}

void Player::die()
{
	printQueue(L"You lose.", Cords(55, 1));
	printQueue(L"Esc to exit", Cords(56, 2));
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
