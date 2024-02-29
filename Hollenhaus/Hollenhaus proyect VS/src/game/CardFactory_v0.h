#pragma once

#include "Factory.h"


class CardFactory_v0 : public Factory {

	float cardScale = 0.55f;
	//EffectCollection collecion;
	
public:
	ecs::entity_t createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable) override;
	ecs::entity_t createDropDetector(Vector2D pos = Vector2D(0,0)) override;
	ecs::entity_t createDropDetector_v2(Vector2D pos = Vector2D(0,0)) ;

	ecs::entity_t createBoard() override;
	void createHand() override;

};
