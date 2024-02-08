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

Game& Game::playerCollide(wchar_t obj, Cords cords)
{
	for (auto& i : enemies)
		if (i == cords)
		{
			playerCollide(&i);
			break;
		}
	for (auto& i : projectiles)
		if (i == cords)
		{
			playerCollide(&i);
			break;
		}

	switch (obj)
	{
	case L'+':
		p1->takeDamage();
		break;
	default:
		break;
	}

	if (p1->checkState())
		takeControls();
	return *this;
}

Game& Game::playerCollide(Entity* ent)
{
	ent->attack(p1);

	if (ent->getType() == 2)
		for (int i = 0; i < projectiles.size(); i++)
			if (projectiles.at(i) == *ent)
			{
				deleteEntity(&projectiles.at(i));
				break;
			}

	return *this;
}

Game& Game::projectileCollide(Entity* projectile, wchar_t obj)
{
	if (obj == p1->getIcon())
		playerCollide(projectile);

	deleteEntity(projectile);
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles.at(i) == *projectile)
		{
			projectiles.erase(projectiles.begin() + i);
			//projectiles_threads.at(i).join();
			//projectiles_threads.at(i).detach();
			//projectiles_threads.erase(projectiles_threads.begin() + i);
		}
	}

	return *this;
}

Game::Game()
{
	player_have_controls = false;
	p1 = nullptr;
	enemies = {};
	projectiles = {};
}

Game::Game(int top_pos, int left_pos, short length, short width) : GameBox(top_pos, left_pos, length, width)
{
	projectiles = {};
	enemies = {};
	player_have_controls = false;
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

Game& Game::moveEntity(Cords new_cords, Entity* ent)
{
	field.at(ent->getY()).at(ent->getX()) = L' ';
	setCursorPosition(Cords(ent->getX() + x, ent->getY() + y));
	std::wcout << field.at(ent->getY()).at(ent->getX());

	if (field.at(new_cords.getY()).at(new_cords.getX()) != L' ')
		if (ent->getType() == 2)
		{
			projectileCollide(ent, field.at(new_cords.getY()).at(new_cords.getX()));
			return *this;
		}

	ent->setCords(new_cords);
	initEntity(ent);
	return *this;
}

void projectileAi(Projectile* projectile, Game& game)
{
	while (true)
	{
		Sleep(50);

		switch (projectile->getDirrection())
		{
		case L'A':
			game.moveEntity(Cords(projectile->getX(), projectile->getY() - 1), projectile);
			break;
		case L'B':
			game.moveEntity(Cords(projectile->getX(), projectile->getY() + 1), projectile);
			break;
		case L'C':
			game.moveEntity(Cords(projectile->getX() + 1, projectile->getY()), projectile);
			break;
		case L'D':
			game.moveEntity(Cords(projectile->getX() - 1, projectile->getY()), projectile);
			break;
		default:
			break;
		}
	}
}

Game& Game::givePlayerControls()
{
	player_have_controls = true;
	while (player_have_controls)
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
	player_have_controls = false;
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

		initEntity(p1);

		p1->printInfo();

		return *this;
	case 1:
		enemies.push_back(Enemy(icon, max_hp, hp, damage));
		enemies.at(enemies.size() - 1).setCords(cords);

		initEntity(&enemies.at(enemies.size() - 1));

		break;
	case 2:
	{
		projectiles.push_back(Projectile(L'C', icon, damage));
		projectiles.at(projectiles.size() - 1).setCords(cords);

		initEntity(&projectiles.at(projectiles.size() - 1));
		std::thread tmp_thr(&projectileAi, &projectiles.at(projectiles.size() - 1), std::ref(*this));
		//projectiles_threads.push_back(tmp_thr);
		tmp_thr.detach();
		break;
	}
	default:
		break;
	}
	return *this;
}

Game& Game::initEntity(Entity* ent)
{
	field.at(ent->getY()).at(ent->getX()) = ent->getIcon();
	setCursorPosition(Cords(ent->getX() + x, ent->getY() + y));
	std::wcout << field.at(ent->getY()).at(ent->getX());

	return *this;
}

Game& Game::deleteEntity(Entity* ent)
{
	field.at(ent->getY()).at(ent->getX()) = L' ';
	setCursorPosition(Cords(ent->getX() + x, ent->getY() + y));
	std::wcout << field.at(ent->getY()).at(ent->getX());

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
			return playerCollide(field.at(p1->getY() - amount).at(p1->getX()), Cords(p1->getX(), p1->getY() - amount));
		}

		moveObject(Cords(p1->getX(), p1->getY() - amount), Cords(p1->getX(), p1->getY()));

		p1->setCords(Cords(p1->getX(), p1->getY() - amount));

		break;
	case L'B':
		if (field.at(p1->getY() + amount).at(p1->getX()) != L' ')
		{
			return playerCollide(field.at(p1->getY() + amount).at(p1->getX()), Cords(p1->getX(), p1->getY() + amount));
		}

		moveObject(Cords(p1->getX(), p1->getY() + amount), Cords(p1->getX(), p1->getY()));

		p1->setCords(Cords(p1->getX(), p1->getY() + amount));

		break;
	case L'C':
		if (field.at(p1->getY()).at(p1->getX() + amount) != L' ')
		{
			return playerCollide(field.at(p1->getY()).at(p1->getX() + amount), Cords(p1->getX() + amount, p1->getY()));
		}

		moveObject(Cords(p1->getX() + amount, p1->getY()), Cords(p1->getX(), p1->getY()));

		p1->setCords(Cords(p1->getX() + amount, p1->getY()));

		break;
	case L'D':
		if (field.at(p1->getY()).at(p1->getX() - amount) != L' ')
		{
			return playerCollide(field.at(p1->getY()).at(p1->getX() - amount), Cords(p1->getX() - amount, p1->getY()));
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
	for (auto& i : projectiles_threads)
		i.detach();
	for (auto& i : enemies_threads)
		i.detach();
	p1 = nullptr;
}
