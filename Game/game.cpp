﻿#include "game.h"

GameBox::GameBox()
{
	cords.setX(0);
	cords.setY(0);
	length = 10;
	width = 10;
	field = {};
}

GameBox::GameBox(int top_pos, int left_pos, short length, short width)
{
	this->cords.setY(top_pos);
	this->cords.setX(left_pos);
	this->length = length;
	this->width = width;

	field.push_back({});
	field.at(0).push_back(L'┌');
	for (int i = 1; i < length - 1; i++)
	{
		field.at(0).push_back(L'─');
	}
	field.at(0).push_back(L'┐');

	for (int i = 1; i < width - 1; i++)
	{
		field.push_back({});
		field.at(i).push_back(L'│');
		for (int j = 1; j < length - 1; j++)
		{
			field.at(i).push_back(L' ');
		}
		field.at(i).push_back(L'│');
	}
	field.push_back({});
	field.at(field.size() - 1).push_back(L'└');
	for (int i = 1; i < length - 1; i++)
	{
		field.at(field.size() - 1).push_back(L'─');
	}
	field.at(field.size() - 1).push_back(L'┘');
}

void setCursorPosition(Cords cords)
{
	std::wcout << L"\u001b[" << cords.getY() << L";" << cords.getX() << L"H";
}

void GameBox::gameBoxPrint()
{
	setCursorPosition(cords);

	for (int i = 0; i < field.size() - 1; i++)
	{
		for (int j = 0; j < field.at(i).size(); j++)
		{
			std::wcout << field.at(i).at(j);
		}
		setCursorPosition(Cords(cords.getX(), cords.getY() + i + 1));
	}
	for (int i = 0; i < field.at(field.size() - 1).size(); i++)
	{
		std::wcout << field.at(field.size() - 1).at(i);
	}
}

void hideCursor()
{
	std::wcout << L"\u001b[?25l";
}

Game::Game()
{
	p1 = nullptr;
}

Game::Game(int top_pos, int left_pos, short length, short width) : GameBox(top_pos, left_pos, length, width)
{
	p1 = nullptr;
}

Game& Game::addObject(Cords cords, wchar_t obj)
{
	if (field.at(cords.getY()).at(cords.getX()) != p1->getIcon())
	{
		field.at(cords.getY()).at(cords.getX()) = obj;
		setCursorPosition(Cords(cords.getX() + this->cords.getX(), cords.getY() + this->cords.getY()));
		std::wcout << obj;
	}
	return *this;
}

Game& Game::giveControls(bool& have_controls)
{
	have_controls = true;
	while (have_controls)
	{
		if (_kbhit())
		{
			int dir = _getch();

			switch (dir)
			{
			case 72:
				movePlayer('A', 1);
				break;
			case 75:
				movePlayer('D', 1);
				break;
			case 77:
				movePlayer('C', 1);
				break;
			case 80:
				movePlayer('B', 1);
				break;
			default:
				break;
			}
		}
	}

	return *this;
}

Game& Game::takeControls(bool& have_controls)
{
	have_controls = false;
	return *this;
}

Game& Game::createPlayer(Cords cords,int id, wchar_t icon, int max_hp, int hp, int damage)
{
	if (p1 != nullptr)
		return *this;

	p1 = new Player(id, icon, max_hp, hp, damage);
	p1->setCords(cords);

	field.at(p1->getCords().getY()).at(p1->getCords().getX()) = p1->getIcon();

	return *this;
}

Game& Game::movePlayer(wchar_t dir, short amount)
{
	Cords previous_player_cords(p1->getX() + cords.getX(), p1->getY() + cords.getY());
	switch (dir)
	{
	case L'A':
		if (field.at(p1->getY() - amount).at(p1->getX()) != L' ')
			return *this;

		field.at(p1->getY() - amount).at(p1->getX()) = p1->getIcon();
		field.at(p1->getY()).at(p1->getX()) = L' ';

		p1->setCords(Cords(p1->getX(), p1->getY() - amount));

		break;
	case L'B':
		if (field.at(p1->getY() + amount).at(p1->getX()) != L' ')
			return *this;

		field.at(p1->getY() + amount).at(p1->getX()) = p1->getIcon();
		field.at(p1->getY()).at(p1->getX()) = L' ';

		p1->setCords(Cords(p1->getX(), p1->getY() + amount));

		break;
	case L'C':
		if (field.at(p1->getY()).at(p1->getX() + amount) != L' ')
			return *this;

		field.at(p1->getY()).at(p1->getX() + amount) = p1->getIcon();
		field.at(p1->getY()).at(p1->getX()) = L' ';

		p1->setCords(Cords(p1->getX() + amount, p1->getY()));

		break;
	case L'D':
		if (field.at(p1->getY()).at(p1->getX() - amount) != L' ')
			return *this;

		field.at(p1->getY()).at(p1->getX() - amount) = p1->getIcon();
		field.at(p1->getY()).at(p1->getX()) = L' ';

		p1->setCords(Cords(p1->getX() - amount, p1->getY()));

		break;
	}

	setCursorPosition(previous_player_cords);

	std::wcout << L" \u001b[1D\u001b[" << amount << dir << p1->getIcon();
	return *this;
}

Game::~Game()
{
	p1 = nullptr;
}
