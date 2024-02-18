#pragma once
#include <string>
#include "game/Entity.h"



class Card //: public ecs::Entity
{
	// lo de adelante es placeholder! para comprobar que funca bien el parseado de jsons que todavia no hay entities ni componentes
	int cost, value;
	std::string sprite, skills;
	int player; // 0 nadie; 1 player; 2 enemigo
	std::string effectHistory;

public:
	Card();
	Card(int, int, std::string&, std::string&, int);

	// añade un efecto al historial de efectos
	void AddEffect(std::string newEffect);

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

	std::string getEffectHistory() {
		return effectHistory;
	}

	
};
