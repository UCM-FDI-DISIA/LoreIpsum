#pragma once

#include "Factory.h"

class CardFactory_v0 : public Factory {

	float cardScale = 0.25f;
public:
	ecs::entity_t createCard(Vector2D pos) override;
	ecs::entity_t createDropDetector(Vector2D pos = Vector2D(0,0)) override;

	void createBoard() override;
	void createHand() override;

};
