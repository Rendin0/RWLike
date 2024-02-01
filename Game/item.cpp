#include "item.h"

Item::Item()
{
	id = -1;
	name = "God";
	description = "God";
	type = -1;
	attributes = {};
}

Item::Item(std::string name, std::string description, int type, std::vector<Attribute> attributes)
{
	this->name = name;
	this->description = description;
	this->type = type;
	this->attributes = attributes;
	
	id = total_items;
	total_items++;
}

std::string Item::getName()
{
	return name;
}

std::string Item::getDescription()
{
	return description;
}

int Item::getId()
{
	return id;
}

int Item::getType()
{
	return type;
}

Attribute::Attribute()
{
	name = "God Att";
	id = -1;
}

Attribute::Attribute(std::string name)
{
	this->name = name;
	id = total_attributes;
	total_attributes++;
}

std::string Attribute::getName()
{
	return name;
}

int Attribute::getId()
{
	return id;
}