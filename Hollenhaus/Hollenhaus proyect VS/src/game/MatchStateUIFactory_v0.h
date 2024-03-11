#pragma once
#include "MatchStateUIFactory.h"
class MatchStateUIFactory_v0 :
    public MatchStateUIFactory
{

public:

	MatchStateUIFactory_v0() : MatchStateUIFactory(){};
	virtual ~MatchStateUIFactory_v0() {};

	ecs::entity_t createVisual_NextTurnButton(int posX, int posY) override;
	ecs::entity_t createVisual_ActionPointsCounter(int posX, int posY) override;
	ecs::entity_t createVisual_ScoreCounter(int posX, int posY, SDL_Color color) override;
	ecs::entity_t createVisual_PlayerTurnIndicator(int posX, int posY) override;
	ecs::entity_t createVisual_BackgroundBlackBox(int posX, int posY, float xPixelsSize, float yPixelsSize) override;
};

