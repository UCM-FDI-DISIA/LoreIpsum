#pragma once

#include "CardFactory.h"

class CardFactory_v0 : public CardFactory {

public:
	ecs::entity_t createCard() override;
	ecs::entity_t createDropDetector() override;


};
