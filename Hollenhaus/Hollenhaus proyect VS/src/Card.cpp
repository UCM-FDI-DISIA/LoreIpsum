#include "Card.h"
#include <string>

Card::Card() 
{
}

Card::Card(int cost, int value) : cost(cost), value(value)
{
}

Card::Card(int cost, int value, std::string& skill) : cost(cost), value(value), skills(skill)
{
}

Card::Card(int cost, int value, std::string& sprite, std::string& skills) 
	: cost(cost), value(value), sprite(sprite), skills(skills)
{
}

Card::Card(int cost, int value, std::string& sprite, SDLEventCallback& effectCallback)
	: cost(cost), value(value), sprite(sprite), effectCallback(effectCallback)
{
}

