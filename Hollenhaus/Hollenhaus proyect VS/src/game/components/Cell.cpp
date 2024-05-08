#include <../pchs/pch.h>

#include "Cell.h"

Cell::Cell() : active(true), corner(false), center(false), totalValue(0), player(Players::NONE), card(nullptr)
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

Cell::Cell(Card* card, Players::Owner own) : active(true), player(own), card(card)
{
	if (card == nullptr) // si NO hay carta en la casilla 
		totalValue = 0;
	else totalValue += card->getValue(); // si hay carta
}


Cell::~Cell()
{
	//delete card;
}


void Cell::addEffect(SDLEventCallback effectCallback)
{
	// desde fuera usar:
	// card->addEffect([this, x]() { efecto(x); });
	// x si hiciera falta algun parametro para el metodo

	if (card != nullptr && effectCallback != nullptr)
	{
		// el effect callback a pasar debera ser el efecto que tenga la carta: card->getEffect()
		effectCallbacks.push_back(effectCallback);
	}
}

void Cell::applyValue(Card* card)
{
	totalValue += card->getValue(); // aplica el valor base
	emit(); // 'emite' los efectos que tienen la carta de esta celda
}

void Cell::addTotal(int add)
{
	if (card != nullptr) // si la carta existe, se le anyade el valor indicado al valor acumulado de la celda
		totalValue += add;
}

void Cell::cleanEffectList()
{
	effectCallbacks.clear(); // limpia la lista de esta celda
}

void Cell::setCard(Card* c, Players::Owner o)
{
	card = c; // le pone la carta indicada a la celda
	player = o; // le pone el player indicado a la celda, a quien le pertenece la carta
}

void Cell::blockEffects(Cell* c)
{
	 c->cleanEffectList(); // elimina todos los efectos de la celda
}

void Cell::emit() const
{
	for (SDLEventCallback cellCallback : effectCallbacks) {
		cellCallback(); // llama a todas las funciones registradas
		//this->getEntity()->getComponent<SpriteRenderer>()->setMultiplyColor(104, 52, 177, 200);
	}
		
}