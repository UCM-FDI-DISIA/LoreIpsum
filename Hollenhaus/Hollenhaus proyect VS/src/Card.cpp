#include "Card.h"
#include <string>

Card::Card(int cost, int value, std::string& sprite, std::string& skills, int player) 
	: cost(cost), value(value), sprite(sprite), skills(skills), player(player)
{


}
