#include "Cell.h"

Cell::Cell(Card* card) : card(card)
{
	if (card != nullptr) isActive = true;
	else isActive = false;

	if (card != nullptr)
		player = card->getPlayer();
	else
		player = 0;
	

}

Cell::Cell(Cell& cell)
{
	card = cell.card;
	isActive = cell.isActive;
	player = cell.player;
}

Cell::Cell()
{
	card = nullptr;
	isActive = false;
	player = 0;
}

