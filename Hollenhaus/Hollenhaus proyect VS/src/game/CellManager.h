#pragma once
#include "ComponentUpdate.h"
class CellManager : public ComponentUpdate
{
public:
	CellManager();

	ecs::entity_t GetCard() { return _card; }
	void SetCard(ecs::entity_t card) { _card = card; }

private:
	ecs::entity_t _card;
};

