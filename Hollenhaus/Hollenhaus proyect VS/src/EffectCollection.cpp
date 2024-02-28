#include "EffectCollection.h"


EffectCollection::EffectCollection()
{
}

void EffectCollection::addValueAdj(Cell* thisCardCell, CellData::Direction direction, int add, bool ultimateArrow)
{
	if (thisCardCell != nullptr)
	{
		if (ultimateArrow)
		{
			while (thisCardCell->getAdjacents()[direction] != nullptr)
			{
				// sobrescribes la celda que mirar
				thisCardCell->getAdjacents()[direction]->addTotal(add);
				thisCardCell = thisCardCell->getAdjacents()[direction];
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

void EffectCollection::blockCard(Cell* thisCardCell, CellData::Direction direction)
{
	if (thisCardCell->getAdjacents()[direction] != nullptr 
		&& thisCardCell->getAdjacents()[direction]->getCard() != nullptr
		&& thisCardCell->getAdjacents()[direction]->getCard()->getIsUnblockable() != true)
	{
		thisCardCell->blockEffects(thisCardCell->getAdjacents()[direction]);
	}
}

void EffectCollection::unblockable(Cell* thisCardCell, bool isUnblockable)
{
	if (thisCardCell != nullptr)
	{
		thisCardCell->getCard()->setUnblockable(isUnblockable);
	}
}