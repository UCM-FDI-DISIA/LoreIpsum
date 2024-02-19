#include "EffectCollection.h"


void EffectCollection::addValueAdj(Direction, int add, bool ultimateArrow)
{

}

void EffectCollection::addValueCenter(int boardSide, int add, Cell* cardCell)
{
	if (cardCell->isCenter()) {

		cardCell->addTotal(add);
	}
}

void EffectCollection::addValueCorner()
{

}

bool EffectCollection::unblockable()
{
	return true;
}
