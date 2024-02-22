#pragma once

#include "CardFactory.h"

class CardFactory_v0 : public CardFactory {

public:
	ecs::entity_t createCard() override;
	ecs::entity_t createDropDetector(Vector2D pos = Vector2D(0,0)) override;


};
