#include "EffectCollection.h"


EffectCollection::EffectCollection()
{
}

void EffectCollection::addAdj(Cell* cell, CellData::Direction direction, int add, bool ultimateArrow)
{
	if (cell != nullptr)
	{
		if (ultimateArrow)
		{
			while (cell->getAdjacents()[direction] != nullptr)
			{
				// sobrescribes la celda que mirar
				cell->getAdjacents()[direction]->addTotal(add);
				cell = cell->getAdjacents()[direction];
			}
		}
		else if (cell->getAdjacents()[direction] != nullptr)
		{
			cell->getAdjacents()[direction]->addTotal(add);
		}
	}
}

void EffectCollection::addSimpleAdj(Cell* cell, CellData::Direction direction, int add)
{
	if (cell != nullptr)
	{
		if (cell->getAdjacents()[direction] != nullptr)
		{
			cell->getAdjacents()[direction]->addTotal(add);
		}
	}
}

void EffectCollection::addSuperAdj(Cell* cell, CellData::Direction direction, int add)
{
	if (cell != nullptr)
	{
		while (cell->getAdjacents()[direction] != nullptr)
		{
			// sobrescribes la celda que mirar
			cell->getAdjacents()[direction]->addTotal(add);
			cell = cell->getAdjacents()[direction];
		}
	}
}

void EffectCollection::addCenter(Cell* cell, int add)
{
	if (cell->getCenter())
	{
		cell->addTotal(add);
	}
}

void EffectCollection::addCorner(Cell* cell, int add)
{
	if (cell->getCorner())
	{
		cell->addTotal(add);
	}
}

void EffectCollection::blockCard(Cell* cell, CellData::Direction direction)
{
	if (cell->getAdjacents()[direction] != nullptr
		&& cell->getAdjacents()[direction]->getCard() != nullptr
		&& cell->getAdjacents()[direction]->getCard()->getIsUnblockable() != true)
	{
		cell->blockEffects(cell->getAdjacents()[direction]);
	}
}

void EffectCollection::unblockable(Cell* cell, bool isUnblockable)
{
	if (cell != nullptr)
	{
		cell->getCard()->setUnblockable(isUnblockable);
	}
}


