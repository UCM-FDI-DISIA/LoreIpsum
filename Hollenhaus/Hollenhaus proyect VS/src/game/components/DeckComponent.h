#pragma once

#include "ComponentUpdate.h"

#include <list>

#include "..\Namespaces.h"

class Card;

class DeckComponent : public ComponentUpdate
{
public:
	DeckComponent() { drawCardCost = 1; }
	~DeckComponent(){}

	void addCartToDeck(Card* card);

	int deckSize() { return deck.size(); }
	
	Card* drawCard();
	void shuffle();

	int getDrawCardCost() const { return drawCardCost; };

	void setOwner(Players::Owner value) { owner = value;}
	Players::Owner getOwner() const { return owner; }

private:
	std::list<Card*> deck;
	int drawCardCost;
	Players::Owner owner;

	void removeCard(Card* c);
	void addCardsOnBottom(std::list<Card*> h);
};

