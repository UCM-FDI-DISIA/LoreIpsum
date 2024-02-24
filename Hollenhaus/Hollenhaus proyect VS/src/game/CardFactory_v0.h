#pragma once

#include "CardFactory.h"

class CardFactory_v0 : public CardFactory {

	float cardScale = 0.25f;
public:
	ecs::entity_t createCard() override;
	ecs::entity_t createDropDetector(Vector2D pos = Vector2D(0,0)) override;

	void createBoard() override;

};
