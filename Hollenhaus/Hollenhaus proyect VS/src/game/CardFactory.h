#pragma once

#include "Entity.h"

class CardFactory
{
public:
	virtual ecs::entity_t createCard() = 0;

};

