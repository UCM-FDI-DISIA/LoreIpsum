#pragma once
#include <string>
#include "Entity.h"
#include <functional>
#include "ComponentUpdate.h"

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void()>;

class Card : public ComponentUpdate
{
	int cost, value;
	std::string sprite; // esto será posteriormente un Texture*
	bool unblockable;
	std::list<SDLEventCallback> cardEffectCallbacks; // lista de los efectos que tiene una carta concreta
	std::list<SDLEventCallback>::iterator cardEffectIT;

public:
	Card();
	Card(int, int);
	Card(int, int, std::string&, bool);

	// getters
	int getCost() const { return cost; }
	int getValue() const { return value; }
	SDLEventCallback getEffect(int i) {
		cardEffectIT = cardEffectCallbacks.begin();
		std::next(cardEffectIT, i);	// avanza x posiciones
		return *(cardEffectIT);
	}
	bool getIsUnblockable() const { return unblockable;  }
	int getEffectSize() const { return cardEffectCallbacks.size(); }

	// setters
	void setCost(int v) { cost = v; }
	void setValue(int v) { value = v; }
	void setSprite(const std::string& v) { sprite = v; }
	void setUnblockable(bool isUnblockable) { unblockable = isUnblockable;  }

	/// 
	void addCardEffect(SDLEventCallback buttonCallback);
};
