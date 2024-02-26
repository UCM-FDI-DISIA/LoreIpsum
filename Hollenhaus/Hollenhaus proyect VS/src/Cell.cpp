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

	// 'emite' los efectos que tienen la carta de esta celda
	emit();

}

void Cell::addTotal(int add)
{
	// si la carta existe, se le añade el valor indicado al valor acumulado de la celda
	if (card != nullptr)
		totalValue += add;
}

void Cell::cleanEffectList()
{
	// limpia la lista de esta celda
	effectCallbacks.clear();
}

void Cell::setCard(Card* c, Owner o)
{
	// le pone la carta indicada a la celda
	card = c;
	// le pone el player indicado a la celda, a quien le pertenece la carta
	player = o;
}

void Cell::blockEffects(Cell* c)
{
	// elimina todos los efectos de la celda
	 c->cleanEffectList();
}

void Cell::emit() const
{
	// llama a todas las funciones registradas
	for (SDLEventCallback cellCallback : effectCallbacks)
		cellCallback();
}