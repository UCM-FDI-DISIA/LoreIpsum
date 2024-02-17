#pragma once
#include <string>
// #include "Entity.h"

class Card // : Entity
{
	// lo de adelante es placeholder! para comprobar que funca bien el parseado de jsons que todavia no hay entities ni componentes
	int cost, value;
	std::string sprite, skills;
	int player; // 0 nadie; 1 player; 2 enemigo
public:
	Card() = default;
	Card(int, int, std::string&, std::string&, int);

	int getCost() {
		return cost;
	}

	int getValue() {
		return value;
	}

	std::string getSkill() {
		return skills;
	}

	int getPlayer() {
		return player;
	}

	
};
