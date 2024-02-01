#pragma once
#include <vector>
#include <string>

class Item
{
	std::string name;
	std::string description;

	int id;
	int type; // 0 - passive, 1 - active, etc.

	std::vector<Attribute> attributes;

	static int total_items;
public:
	Item();
	Item(std::string name, std::string description, int type, std::vector<Attribute> attributes);

	std::string getName();
	std::string getDescription();

	int getId();
	int getType();
};

class Attribute
{
	std::string name;

	int id;

	static int total_attributes;
public:
	Attribute();
	Attribute(std::string name);

	std::string getName();
	
	int getId();
};