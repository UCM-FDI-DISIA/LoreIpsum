#include "Cell.h"

Cell::Cell(Card* card) : card(card)
{
	if (card != nullptr) isActive = true;
	else isActive = false;

	isPlayer = card->getPlayer();

}
