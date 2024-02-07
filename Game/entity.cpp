#include "entity.h"

Entity::Entity()
{
	id = type = max_hp = hp = damage = icon = -1;
}

Entity::Entity(int type, wchar_t icon, int max_hp, int hp, int damage)
{
	this->id = total_enityties;
	total_enityties++;
	this->type = type;
	this->icon = icon;
	this->max_hp = max_hp;
	this->hp = hp;
	this->damage = damage;
}

void Entity::die()
{
	return;
}

bool Entity::checkState()
{
	if (hp <= 0)
		die();
	return hp > 0;
}

wchar_t Entity::getIcon()
{
	return icon;
}

Entity& Entity::setIcon(wchar_t icon)
{
	this->icon = icon;
	return *this;
}

Entity& Entity::takeDamage(int value)
{
	hp -= value;
	return *this;
}

Entity& Entity::takeDamage()
{
	return takeDamage(1);
}

Entity& Entity::heal(int value)
{
	hp += value;
	if (hp > max_hp)
		hp = max_hp;
	return *this;
}

Entity& Entity::heal()
{
	return heal(1);
}

int Entity::getMaxHp()
{
	return max_hp;
}

int Entity::getHp()
{
	return hp;
}

int Entity::getDamage()
{
	return damage;
}

int Entity::getType()
{
	return type;
}

Entity& Entity::attack(Entity* ent)
{
	ent->takeDamage(damage);
	return *this;
}

Entity& Entity::setMaxHp(int max_hp)
{
	this->max_hp = max_hp;
	return *this;
}

Entity& Entity::setHp(int hp)
{
	this->hp = hp;
	return *this;
}

Entity& Entity::setDamage(int damage)
{
	this->damage = damage;
	return *this;
}
