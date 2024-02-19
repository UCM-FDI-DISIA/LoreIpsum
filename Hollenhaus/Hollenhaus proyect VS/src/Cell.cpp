#include "Cell.h"

Cell::Cell(Card* card, Owner own) : active(true), player(own), card(card)
{
	// si NO hay carta en la casilla 
	if (card == nullptr) {
		totalValue = 0;
	}
	// si hay carta
	else totalValue = card->getValue();
}

Cell::~Cell()
{
	delete card;
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

Cell::Cell()
{
	card = nullptr;
	active = false;
	player = NONE;
}

void Cell::addEffect(std::string)
{

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


