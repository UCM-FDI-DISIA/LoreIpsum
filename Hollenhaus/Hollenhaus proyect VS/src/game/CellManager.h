#pragma once
#include "ComponentUpdate.h"
#include "../utils/Vector2D.h"


class Entity;

class CellManager : public ComponentUpdate
{
public:
	CellManager();

	/// getters
	ecs::entity_t getCard() const { return _card; }
	Vector2D& getPosOnBoard() { return posOnBoard; }

	/// setters
	bool setCard(ecs::entity_t card);
	void setPosOnBoard(int posX, int posY);
	void setPosOnBoard(Vector2D pos);

private:
	ecs::entity_t _card;
	Vector2D posOnBoard;
};

