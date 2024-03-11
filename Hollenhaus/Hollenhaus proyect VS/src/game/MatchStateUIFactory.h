#pragma once

#include "../sdlutils/SDLUtils.h"


class MatchStateUIFactory
{

public:

	MatchStateUIFactory() {};
	virtual ~MatchStateUIFactory() {};

	virtual ecs::entity_t createVisual_NextTurnButton() = 0;
	virtual ecs::entity_t createVisual_ActionPointsCounter() = 0;
	virtual ecs::entity_t createVisual_ScoreCounter() = 0;
	virtual ecs::entity_t createVisual_PlayerTurnIndicator() = 0;

};