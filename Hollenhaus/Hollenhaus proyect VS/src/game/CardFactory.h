#pragma once

#include "../sdlutils/SDLUtils.h"


class CardFactory
{

public:

	CardFactory(){};
	virtual ~CardFactory(){};

	virtual ecs::entity_t 
		createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<SDLUtils::CardEffect>& effects) = 0;

	virtual void createHand() =0;

};

