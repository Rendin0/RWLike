#include "game.h"

GameBox::GameBox()
{
	x = 0;
	y = 0;
	length = 10;
	width = 10;
	field = {};
}

GameBox::GameBox(int top_pos, int left_pos, short length, short width)
{
	this->y = top_pos;
	this->x = left_pos;
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

void GameBox::gameBoxPrint()
{
	setCursorPosition(Cords(x, y));

	for (int i = 0; i < field.size() - 1; i++)
	{
		for (int j = 0; j < field.at(i).size(); j++)
		{
			std::wcout << field.at(i).at(j);
		}
		setCursorPosition(Cords(x, y + i + 1));
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

Game& Game::playerCollide(wchar_t obj)
{
	switch (obj)
	{
	case L'+':
		p1->takeDamage();
		break;
	case L'·':
		p1->takeDamage(2);
		break;
	default:
		break;
	}

	if (p1->checkState())
		takeControls();
	return *this;
}

Game::Game()
{
	have_controls = false;
	p1 = nullptr;
}

Game::Game(int top_pos, int left_pos, short length, short width) : GameBox(top_pos, left_pos, length, width)
{
	have_controls = false;
	p1 = nullptr;
}

Game& Game::addObject(Cords cords, wchar_t obj)
{
	if (field.at(cords.getY()).at(cords.getX()) != p1->getIcon())
	{
		field.at(cords.getY()).at(cords.getX()) = obj;
		setCursorPosition(Cords(cords.getX() + this->x, cords.getY() + this->y));
		std::wcout << obj;
	}
	return *this;
}

Game& Game::moveObject(Cords new_cords, Cords old_cords)
{
	field.at(new_cords.getY()).at(new_cords.getX()) = field.at(old_cords.getY()).at(old_cords.getX());
	field.at(old_cords.getY()).at(old_cords.getX()) = L' ';
	return *this;
}

Game& Game::giveControls()
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

Game& Game::takeControls()
{
	have_controls = false;
	return *this;
}

Game& Game::createEntity(Cords cords, int type, wchar_t icon, int max_hp, int hp, int damage)
{
	switch (type)
	{
	case 0:
		if (p1 != nullptr)
			return *this;

		p1 = new Player(icon, max_hp, hp, damage);
		p1->setCords(cords);

		field.at(p1->getY()).at(p1->getX()) = p1->getIcon();

		p1->printInfo();

		return *this;
	default:
		break;
	}
	return *this;
}

Game& Game::movePlayer(wchar_t dir, short amount)
{
	Cords previous_player_cords(p1->getX() + x, p1->getY() + y);
	switch (dir)
	{
	case L'A':
		if (field.at(p1->getY() - amount).at(p1->getX()) != L' ')
		{
			return playerCollide(field.at(p1->getY() - amount).at(p1->getX()));
		}

		moveObject(Cords(p1->getX(), p1->getY() - amount), Cords(p1->getX(), p1->getY()));

		p1->setCords(Cords(p1->getX(), p1->getY() - amount));

		break;
	case L'B':
		if (field.at(p1->getY() + amount).at(p1->getX()) != L' ')
		{
			return playerCollide(field.at(p1->getY() + amount).at(p1->getX()));
		}

		moveObject(Cords(p1->getX(), p1->getY() + amount), Cords(p1->getX(), p1->getY()));

		p1->setCords(Cords(p1->getX(), p1->getY() + amount));

		break;
	case L'C':
		if (field.at(p1->getY()).at(p1->getX() + amount) != L' ')
		{
			return playerCollide(field.at(p1->getY()).at(p1->getX() + amount));
		}

		moveObject(Cords(p1->getX() + amount, p1->getY()), Cords(p1->getX(), p1->getY()));

		p1->setCords(Cords(p1->getX() + amount, p1->getY()));

		break;
	case L'D':
		if (field.at(p1->getY()).at(p1->getX() - amount) != L' ')
		{
			return playerCollide(field.at(p1->getY()).at(p1->getX() - amount));
		}

		moveObject(Cords(p1->getX() - amount, p1->getY()), Cords(p1->getX(), p1->getY()));
		
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
