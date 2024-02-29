#pragma once
#include "ComponentUpdate.h"
#include "../utils/Vector2D.h"


class Entity;

class CellManager : public ComponentUpdate
{
public:
	CellManager();

	ecs::entity_t GetCard() { return _card; };

	bool setCard(ecs::entity_t card);

	void setPosOnBoard(int posX, int posY);
	void setPosOnBoard(Vector2D pos);
	Vector2D getPosOnBoard() { return posOnBoard; }

private:
	ecs::entity_t _card;

	Vector2D posOnBoard;
};

