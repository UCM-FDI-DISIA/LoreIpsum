#pragma once

#include "../sdlutils/SDLUtils.h"


class MatchStateUIFactory
{

public:

	MatchStateUIFactory() {};
	virtual ~MatchStateUIFactory() {};

	virtual ecs::entity_t createVisual_NextTurnButton(int posX, int posY) = 0;
	virtual ecs::entity_t createVisual_ActionPointsCounter(int posX, int posY) = 0;
	virtual ecs::entity_t createVisual_ScoreCounter(int posX, int posY, SDL_Color color) = 0;
	virtual ecs::entity_t createVisual_PlayerTurnIndicator(int posX, int posY) = 0;
	virtual ecs::entity_t createVisual_BackgroundBlackBox(int posX, int posY, float xPixelsSize, float yPixelsSize) = 0;

};