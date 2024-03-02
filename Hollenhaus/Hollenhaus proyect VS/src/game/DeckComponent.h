#pragma once

#include "ComponentUpdate.h"

#include <list>

class Card;

class DeckComponent : public ComponentUpdate
{
public:
	DeckComponent(){}
	~DeckComponent(){}

	Card* drawCard();

private:
	std::list<Card*> deck;

	void shuffle();
	void removeCard(Card* c);
	void addCardsOnBottom(std::list<Card*> h);
};

