#pragma once
#include <string>
#include "game/Entity.h"
#include <functional>

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void(void)>;

#include "game/ComponentUpdate.h"

class Card : public ComponentUpdate
{
	// lo de adelante es placeholder! para comprobar que funca bien el parseado de jsons que todavia no hay entities ni componentes
	int cost, value;
	std::string sprite, skills;

	std::list<SDLEventCallback> cardEffectCallbacks; // lista de los efectos que tiene una carta concreta

	SDLEventCallback effectCallback;

public:
	Card();
	Card(int, int);
	Card(int, int, std::string&);
	Card(int, int, std::string&, std::string&);

	Card(int, int, std::string&, SDLEventCallback &effectCallback);

	// adds a skill to the skills of the card
	void addSkill(std::string& s) { skills += " " + s; }

	// getters
	int getCost() const { return cost; }
	int getValue() const { return value; }
	std::string getSkill() { return skills; }

	// setters
	void setCost(int v) { cost = v; }
	void setValue(int v) { value = v; }
	void setSprite(const std::string& v) { sprite = v; }
	void setSkills(const std::string& v) { skills = v; }
};
