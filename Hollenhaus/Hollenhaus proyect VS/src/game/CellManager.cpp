#include "CellManager.h"
#include "Entity.h"
CellManager::CellManager() :
	_card(nullptr),
	posOnBoard(-1, -1)
{}


bool CellManager::setCard(ecs::entity_t card)
{
	return true;
}

void CellManager::setPosOnBoard(int posX, int posY)
{
	posOnBoard.setX(posX);
	posOnBoard.setY(posY);
}

void CellManager::setPosOnBoard(Vector2D pos)
{
	posOnBoard = pos;
}
