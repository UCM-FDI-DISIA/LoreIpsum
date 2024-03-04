#pragma once

#include "ComponentUpdate.h"

#include <list>

class Card;

class DeckComponent : public ComponentUpdate
{
public:
	DeckComponent() { drawCardCost = 2; }
	~DeckComponent(){}

	void addCartToDeck(Card* card);

	int deckSize() { return deck.size(); }
	
	Card* drawCard();
	void shuffle();

	int getDrawCardCost() const { return drawCardCost; };

private:
	std::list<Card*> deck;
	int drawCardCost;

	void removeCard(Card* c);
	void addCardsOnBottom(std::list<Card*> h);
};

