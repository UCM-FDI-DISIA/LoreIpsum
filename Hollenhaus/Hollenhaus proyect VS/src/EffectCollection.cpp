#include "EffectCollection.h"


EffectCollection::EffectCollection()
{

}

void EffectCollection::addValueAdj(Cell* thisCardCell, Direction direction, int add, bool ultimateArrow)
{
	if (ultimateArrow) {
		while (thisCardCell->getAdjacents()[direction] != nullptr) {

			// sobrescribes la celda que mirar
			thisCardCell = thisCardCell->getAdjacents()[direction];
			thisCardCell->getAdjacents()[direction]->addTotal(add);
		}
	}
	else {
		thisCardCell->getAdjacents()[direction]->addTotal(add);
	}
}

void EffectCollection::addValueCenter(Cell* thisCardCell, int add)
{
	if (thisCardCell->getCorner()) {

		thisCardCell->addTotal(add);
	}
}

void EffectCollection::addValueCorner(Cell* thisCardCell, int add)
{
	if (thisCardCell->getCorner()) {
		thisCardCell->addTotal(add);
	}
}

void EffectCollection::blockCard(Cell* thisCardCell, Direction direction)
{
	if (thisCardCell->getAdjacents()[direction] != nullptr) {

		thisCardCell->getAdjacents()[direction]->blockEffects(thisCardCell);
	}
}

bool EffectCollection::unblockable()
{
	return true;
}
