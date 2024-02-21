#include "EffectCollection.h"


void EffectCollection::addValueAdj(Cell* cardCell, Direction direction, int add, bool ultimateArrow)
{
	if (ultimateArrow) {
		cardCell->getAdjacents()[direction]->addTotal(add);
	}
	else {

	}
}

void EffectCollection::addValueCenter(int add, Cell* cardCell)
{
	if (cardCell->isCenter()) {

		cardCell->addTotal(add);
	}
}

void EffectCollection::addValueCorner()
{

}

void EffectCollection::blockCard(Direction direction)
{

}


bool EffectCollection::unblockable()
{
	return true;
}
