#pragma once

#include <functional>
#include "ComponentUpdate.h"
#include <string>
// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void()>;

class Cell;

class Card : public ComponentUpdate
{
	int cost, value;	// coste y valor de la carta
	std::string sprite; // esto sera posteriormente un puntero a Texture
	bool unblockable;	// indica si esta carta se puede bloquear o no
	Cell* cell;
	std::list<SDLEventCallback> effects;	// lista de los efectos que tiene una carta concreta
	std::list<SDLEventCallback>::iterator effectIt;	// iterador para recorrer la lista de efectos de la carta

public:
	Card();
	Card(int, int);
	Card(int, int, std::string&, bool);

	// getters
	int getCost() const { return cost; }
	int getValue() const { return value; }
	std::string& getSprite() { return sprite; }
	bool getUnblockable() const { return unblockable;  }
	Cell* getCell() const { return cell;  }
	std::list<SDLEventCallback> getEffects() const { return effects; }
	SDLEventCallback getEffect(int i) {
		if (i < 0) return nullptr;

		effectIt = effects.begin();
		std::next(effectIt, i);	// avanza x posiciones
		return *(effectIt);
	}
	int getEffectSize() const { return effects.size(); }

	// setters
	void setCost(int v) { cost = v; }
	void setValue(int v) { value = v; }
	void setSprite(const std::string& v) { sprite = v; }
	void setUnblockable(bool isUnblockable) { unblockable = isUnblockable;  }
	void setCell(Cell* _cell) { cell = _cell; }

	/// 
	void addCardEffect(SDLEventCallback effectCallback);
};
