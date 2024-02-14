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
	printQueue(L"\u001b[?25l");
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

Game& Game::projectileCollide(std::vector<Projectile> projectiles, size_t index, wchar_t obj)
{
	if (obj == p1->getIcon())
		playerCollide(&projectiles.at(index));

	deleteEntity(&projectiles.at(index));
	projectiles.at(index).die();
	projectiles.erase(projectiles.begin() + index);

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
		printQueue(obj, cords + this->getCords());
	}
	return *this;
}

Game& Game::moveObject(Cords new_cords, Cords old_cords)
{
	field.at(new_cords.getY()).at(new_cords.getX()) = field.at(old_cords.getY()).at(old_cords.getX());
	field.at(old_cords.getY()).at(old_cords.getX()) = L' ';
	return *this;
}

Game& Game::moveEntity(Cords new_cords, std::vector<Projectile> projectiles, size_t index)
{
	field.at(projectiles.at(index).getY()).at(projectiles.at(index).getX()) = L' ';
	printQueue(field.at(projectiles.at(index).getY()).at(projectiles.at(index).getX()), projectiles.at(index).getCords() + getCords());

	if (field.at(new_cords.getY()).at(new_cords.getX()) != L' ')
	{
		projectileCollide(projectiles, index, field.at(new_cords.getY()).at(new_cords.getX()));
		return *this;
	}

	projectiles.at(index).setCords(new_cords);
	initEntity(&projectiles.at(index));
	return *this;
}

Game& Game::moveEntity(Cords new_cords, Entity* ent)
{
	field.at(ent->getY()).at(ent->getX()) = L' ';
	printQueue(field.at(ent->getY()).at(ent->getX()), ent->getCords() + getCords());

	ent->setCords(new_cords);
	initEntity(ent);
	return *this;
}

void projectileAi(std::vector<Projectile>* projectiles, size_t index, Game& game)
{
	time_t time = clock();
	while (projectiles.at(index).getAlive())
	{
		if (clock() - time >= 60)
		{
			switch (projectiles.at(index).getDirrection())
			{
			case L'A':
				game.moveEntity(projectiles.at(index).getCords() - Cords(0, 1), projectiles, index);
				break;
			case L'B':
				game.moveEntity(projectiles.at(index).getCords() + Cords(0, 1), projectiles, index);
				break;
			case L'C':
				game.moveEntity(projectiles.at(index).getCords() + Cords(1, 0), projectiles, index);
				break;
			case L'D':
				game.moveEntity(projectiles.at(index).getCords() - Cords(1, 0), projectiles, index);
				break;
			default:
				break;
			}
			time = clock();
		}

	}
}

void enemyAi(Enemy* enemy, Game& game)
{
	time_t time = clock();
	while (true)
	{
		if (clock() - time >= 1000)
		{
			if (enemy->getShooting())
			{
				game.createEntity(enemy->getCords() - Cords(1, 0), L'D', L'·', enemy->getDamage());
			}
			time = clock();
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

Game& Game::createEntity(Cords cords, wchar_t dir, wchar_t icon, int damage)
{
	projectiles.push_back(Projectile(dir, icon, damage));
	projectiles.at(projectiles.size() - 1).setCords(cords);

	initEntity(&projectiles.at(projectiles.size() - 1));

	projectiles_threads.push_back(std::thread(projectileAi, projectiles, projectiles.size() - 1, std::ref(*this)));  // TODO: After push_back links to all projectiles are changes
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
		enemies.at(enemies.size() - 1).setShooting(true).setCords(cords);

		initEntity(&enemies.at(enemies.size() - 1));

		enemies_threads.push_back(std::thread(enemyAi, &enemies.at(enemies.size() - 1), std::ref(*this)));
		break;
	default:
		break;
	}
	return *this;
}

Game& Game::initEntity(Entity* ent)
{
	field.at(ent->getY()).at(ent->getX()) = ent->getIcon();
	printQueue(field.at(ent->getY()).at(ent->getX()), Cords(ent->getX() + x, ent->getY() + y));

	return *this;
}

Game& Game::deleteEntity(Entity* ent)
{
	field.at(ent->getY()).at(ent->getX()) = L' ';

	printQueue(field.at(ent->getY()).at(ent->getX()), Cords(ent->getX() + x, ent->getY() + y));

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

	printQueue(std::wstring(L" \u001b[1D\u001b[" + std::to_wstring(amount) + dir + p1->getIcon()), previous_player_cords);
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
