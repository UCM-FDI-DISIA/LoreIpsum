#include "EffectCollection.h"


EffectCollection::EffectCollection()
{
}

void EffectCollection::addValueAdj(Cell* thisCardCell, Direction direction, int add, bool ultimateArrow)
{
	if (thisCardCell != nullptr)
	{
		if (ultimateArrow)
		{
			while (thisCardCell->getAdjacents()[direction] != nullptr || thisCardCell->getAdjacents()[direction]->
			                                                             getCard()->getIsUnblockable() != true)
			{
				// sobrescribes la celda que mirar
				thisCardCell = thisCardCell->getAdjacents()[direction];
				thisCardCell->getAdjacents()[direction]->addTotal(add);
			}
		}
		else if (thisCardCell->getAdjacents()[direction] != nullptr)
		{
			thisCardCell->getAdjacents()[direction]->addTotal(add);
		}
	}
}

void EffectCollection::addValueCenter(Cell* thisCardCell, int add)
{
	if (thisCardCell->getCenter())
	{
		thisCardCell->addTotal(add);
	}
}

void EffectCollection::addValueCorner(Cell* thisCardCell, int add)
{
	if (thisCardCell->getCorner())
	{
		thisCardCell->addTotal(add);
	}
}

void EffectCollection::blockCard(Cell* thisCardCell, Direction direction)
{
	if (thisCardCell->getAdjacents()[direction] != nullptr && thisCardCell->getAdjacents()[direction]->getCard()->
		getIsUnblockable() != true)
	{
		thisCardCell->getAdjacents()[direction]->blockEffects(thisCardCell);
	}
}

void EffectCollection::unblockable(Cell* thisCardCell, bool isUnblockable)
{
	if (thisCardCell != nullptr)
	{
		thisCardCell->getCard()->setUnblockable(isUnblockable);
	}
}