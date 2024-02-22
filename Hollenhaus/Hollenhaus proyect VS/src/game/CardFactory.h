#pragma once

#include "Entity.h"
#include "../utils/Vector2D.h"

class CardFactory
{
public:
	virtual ecs::entity_t createCard() = 0;

	virtual ecs::entity_t createDropDetector(Vector2D pos) = 0;

};

