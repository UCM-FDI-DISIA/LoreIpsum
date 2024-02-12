#pragma once
#include <string>
// #include "Entity.h"

class Card // : Entity
{
	// lo de adelante es placeholder! para comprobar que funca bien el parseado de jsons que todavia no hay entities ni componentes
	int cost, value;
	std::string sprite, skills;
public:
	Card() = default;
	Card(int, int, std::string&);
};
