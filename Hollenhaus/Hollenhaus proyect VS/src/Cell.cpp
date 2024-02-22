#include "Cell.h"

Cell::Cell() : active(true), corner(false), center(false), totalValue(0), player(NONE), card(nullptr)
{
}

Cell::Cell(Cell& cell)
{
	card = cell.card;
	active = cell.active;
	player = cell.player;
	adjacents = cell.adjacents;
	effectHistory = cell.effectHistory;
	totalValue = cell.totalValue;
}

Cell::Cell(Card* card, Owner own) : active(true), player(own), card(card)
{
	// si NO hay carta en la casilla 
	if (card == nullptr)
		totalValue = 0;
	// si hay carta
	else totalValue = card->getValue();
}


Cell::~Cell()
{
	delete card;
}


void Cell::addEffect(SDLEventCallback effectCallback)
{
	if (card != nullptr)
	{
		effectCallbacks.push_back(card->getEffect());
	}
}

void Cell::applyValue(Card* card)
{
	// aplica el valor base
	totalValue = card->getValue();

	// aplica el efecto ???
}

void Cell::addTotal(int add)
{
	totalValue += add;
}

void Cell::setCard(Card* c, Owner o)
{
	card = c;
	player = o;
}

void Cell::blockEffects(Card* c)
{
	c->getCardEffects().clear();
}
