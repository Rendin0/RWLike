#pragma once

class Entity
{
protected:
	int id;
	int type;
	wchar_t icon;
	int max_hp, hp;
	int damage;
	static int total_enityties;

public:
	Entity();
	Entity(int type, wchar_t icon, int max_hp, int hp, int damage); // types: 0(player), 1(enemy), 2(projectyle), 3(misc)

	virtual Entity& die();
	virtual bool checkState();

	virtual wchar_t getIcon();
	virtual Entity& setIcon(wchar_t icon);

	virtual Entity& takeDamage(int value);
	virtual Entity& takeDamage();

	virtual Entity& heal(int value);
	virtual Entity& heal();

	virtual int getMaxHp();
	virtual int getHp();
	virtual int getDamage();
	virtual int getType();

	virtual Entity& attack(Entity* ent);

	virtual Entity& setMaxHp(int max_hp);
	virtual Entity& setHp(int hp);
	virtual Entity& setDamage(int damage);
};