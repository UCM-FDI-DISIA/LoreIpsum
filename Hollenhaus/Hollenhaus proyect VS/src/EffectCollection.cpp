#include "EffectCollection.h"


void EffectCollection::addValueAdj(Cell* thisCardCell, Direction direction, int add, bool ultimateArrow)
{
	if (ultimateArrow && (thisCardCell->getAdjacents()[direction] != nullptr)) {
		thisCardCell->getAdjacents()[direction]->addTotal(add);
	}
	else {

	}
}

void EffectCollection::addValueCenter(Cell* thisCardCell, int add)
{
	if (thisCardCell->isCenter()) {

		thisCardCell->addTotal(add);
	}
}

void EffectCollection::addValueCorner(Cell* thisCardCell, int add)
{
	if (thisCardCell->isCorner()) {
		thisCardCell->addTotal(add);
	}
}

void EffectCollection::blockCard(Cell* thisCardCell, Direction direction)
{
	if (thisCardCell->getAdjacents()[direction] != nullptr) {

		thisCardCell->getAdjacents()[direction]->blockEffects(thisCardCell->getCard());
	}
}


bool EffectCollection::unblockable()
{
	return true;
}
