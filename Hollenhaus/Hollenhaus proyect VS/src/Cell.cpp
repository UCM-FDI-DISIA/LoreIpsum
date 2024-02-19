#include "Cell.h"

Cell::Cell(Card* card, Owner own) : active(true), player(own), card(card)
{
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

void Cell::setCard(Card* c, Owner o)
{
	card = c;
	player = o;
}


