#include "Cell.h"

void Cell::emit() const
{
	// llama a todas las funciones registradas
	for (SDLEventCallback cellCallback : effectCallbacks)
		cellCallback();
}

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
	// desde fuera usar:
	// card->addEffect([this]() { efecto(); });

	if (card != nullptr)
	{
		// el effect callback a pasar debera ser el efecto que tenga la carta: card->getEffect()
		effectCallbacks.push_back(effectCallback);
	}
}

void Cell::applyValue(Card* card)
{
	// aplica el valor base
	totalValue = card->getValue();

	// aplica el efecto ???
	// recorre la lista de callbacks
	listIT = effectCallbacks.begin();
	while (listIT != effectCallbacks.end() && (*listIT) != nullptr) {

		(*listIT)();
		++listIT;
	}
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

void Cell::blockEffects(Cell* c)
{
	c->getEffects().clear();
}

