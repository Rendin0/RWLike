#include "game.h"

GameBox::GameBox()
{
	cords.X = 0;
	cords.Y = 0;
	length = 10;
	width = 10;
	field = {};
}

GameBox::GameBox(int top_pos, int left_pos, int length, int width)
{
	this->cords.Y = top_pos;
	this->cords.X = left_pos;
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

void setCursorPosition(COORD cords)
{
	std::wcout << L"\u001b[" << cords.Y << L";" << cords.X << L"H";
}

void GameBox::gameBoxPrint()
{
	setCursorPosition(cords);
	COORD tmp_cord;


	for (int i = 0; i < field.size() - 1; i++)
	{
		for (int j = 0; j < field.at(i).size(); j++)
		{
			std::wcout << field.at(i).at(j);
		}
		tmp_cord.X = cords.X;
		tmp_cord.Y = cords.Y + i + 1;
		setCursorPosition(tmp_cord);
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

Game::Game(int top_pos, int left_pos, int length, int width) : GameBox(top_pos, left_pos, length, width)
{
	p1 = nullptr;
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

Game& Game::createPlayer(int id, wchar_t icon, int max_hp, int hp, int damage)
{
	if (p1 != nullptr)
		return *this;

	p1 = new Player(id, icon, max_hp, hp, damage);

	field.at(p1->getCords().Y).at(p1->getCords().X) = p1->getIcon();

	return *this;
}

Game& Game::movePlayer(wchar_t dir, short amount)
{
	COORD tmp_cord = { p1->getCords().X + cords.X, p1->getCords().Y + cords.Y };
	COORD tmp_cord2;
	switch (dir)
	{
	case L'A':
		if (field.at(p1->getCords().Y - amount).at(p1->getCords().X) != L' ')
			return *this;

		field.at(p1->getCords().Y - amount).at(p1->getCords().X) = p1->getIcon();
		field.at(p1->getCords().Y).at(p1->getCords().X) = L' ';

		tmp_cord2.Y = p1->getCords().Y - amount;
		tmp_cord2.X = p1->getCords().X;
		p1->setCords(tmp_cord2);

		break;
	case L'B':
		if (field.at(p1->getCords().Y + amount).at(p1->getCords().X) != L' ')
			return *this;

		field.at(p1->getCords().Y + amount).at(p1->getCords().X) = p1->getIcon();
		field.at(p1->getCords().Y).at(p1->getCords().X) = L' ';

		tmp_cord2.Y = p1->getCords().Y + amount;
		tmp_cord2.X = p1->getCords().X;
		p1->setCords(tmp_cord2);

		break;
	case L'C':
		if (field.at(p1->getCords().Y).at(p1->getCords().X + amount) != L' ')
			return *this;

		field.at(p1->getCords().Y).at(p1->getCords().X + amount) = p1->getIcon();
		field.at(p1->getCords().Y).at(p1->getCords().X) = L' ';

		tmp_cord2.Y = p1->getCords().Y;
		tmp_cord2.X = p1->getCords().X + amount;
		p1->setCords(tmp_cord2);

		break;
	case L'D':
		if (field.at(p1->getCords().Y).at(p1->getCords().X - amount) != L' ')
			return *this;

		field.at(p1->getCords().Y).at(p1->getCords().X - amount) = p1->getIcon();
		field.at(p1->getCords().Y).at(p1->getCords().X) = L' ';

		tmp_cord2.Y = p1->getCords().Y;
		tmp_cord2.X = p1->getCords().X - amount;
		p1->setCords(tmp_cord2);

		break;
	}

	setCursorPosition(tmp_cord);

	std::wcout << L" \u001b[1D\u001b[" << amount << dir << p1->getIcon();
	return *this;
}

Game::~Game()
{
	p1 = nullptr;
}
