#pragma once
#include <string>
#include "Entity.h"
#include <functional>
#include "ComponentUpdate.h"

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void()>;

class Card : public ComponentUpdate
{
	// lo de adelante es placeholder! para comprobar que funca bien el parseado de jsons que todavia no hay entities ni componentes
	int cost, value;
	std::string sprite;

	std::list<SDLEventCallback> cardEffectCallbacks; // lista de los efectos que tiene una carta concreta
	std::list<SDLEventCallback>::iterator cardEffectIT;

	//SDLEventCallback effectCallback;

public:
	Card();
	Card(int, int);
	Card(int, int, std::string&);

	// getters
	int getCost() const { return cost; }
	int getValue() const { return value; }
	SDLEventCallback getEffect(int i) {

		cardEffectIT = cardEffectCallbacks.begin();
		std::next(cardEffectIT, i);	// avanza x posiciones

		return *(cardEffectIT);
	}

	// setters
	void setCost(int v) { cost = v; }
	void setValue(int v) { value = v; }
	void setSprite(const std::string& v) { sprite = v; }

	void addCardEffect(SDLEventCallback buttonCallback);s
};
