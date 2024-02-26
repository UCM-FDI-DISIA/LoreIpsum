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
	totalValue = cell.totalValue;
}

Cell::Cell(Card* card, Owner own) : active(true), player(own), card(card)
{
	// si NO hay carta en la casilla 
	if (card == nullptr)
		totalValue = 0;
	// si hay carta
	else totalValue += card->getValue();
}


Cell::~Cell()
{
	delete card;
}


void Cell::addEffect(SDLEventCallback effectCallback)
{
	// desde fuera usar:
	// card->addEffect([this, x]() { efecto(x); });
	// x si hiciera falta algun parametro para el metodo

	if (card != nullptr)
	{
		// el effect callback a pasar debera ser el efecto que tenga la carta: card->getEffect()
		effectCallbacks.push_back(effectCallback);
	}
}

void Cell::applyValue(Card* card)
{
	// aplica el valor base
	totalValue += card->getValue();

	emit();

	//// aplica el efecto ???
	//// recorre la lista de callbacks
	//listIT = effectCallbacks.begin();
	//while (listIT != effectCallbacks.end() && (*listIT) != nullptr) {
	//	(*listIT)();
	//	++listIT;
	//}
}

void Cell::addTotal(int add)
{
	if (card != nullptr)
		totalValue += add;
}

void Cell::setCard(Card* c, Owner o)
{
	card = c;
	player = o;
}

void Cell::blockEffects(Cell* c)
{
	listIT = c->getEffects().begin();

	while (listIT != effectCallbacks.end() && (*listIT) != nullptr) {
		c->getEffects().remove(*listIT);
		++listIT;
	}

	/*
	for (int i = 0; i < c->getEffects().size(); i++) {

		c->getEffects().clear();
	}
	*/
}

void Cell::emit() const
{
	// llama a todas las funciones registradas
	for (SDLEventCallback cellCallback : effectCallbacks)
		cellCallback();
}