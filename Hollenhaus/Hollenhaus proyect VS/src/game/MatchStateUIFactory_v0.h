#pragma once
#include "MatchStateUIFactory.h"
class MatchStateUIFactory_v0 :
    public MatchStateUIFactory
{

public:

	MatchStateUIFactory_v0() {};
	virtual ~MatchStateUIFactory_v0() {};

	virtual ecs::entity_t createVisual_NextTurnButton();
	virtual ecs::entity_t createVisual_ActionPointsCounter();
	virtual ecs::entity_t createVisual_ScoreCounter();
	virtual ecs::entity_t createVisual_PlayerTurnIndicator();
};

