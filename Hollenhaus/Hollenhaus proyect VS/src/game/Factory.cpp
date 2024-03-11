#include "pch.h"
#include "Factory.h"
#include "CardFactory.h"
#include "BoardFactory.h"

#include "MatchStateUIFactory.h"

ecs::entity_t Factory::createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<SDLUtils::CardEffect>& effects)
{
	if (cardFactory == nullptr) {
		throw "no existe cardFactory";
	}

	return cardFactory->createCard(pos,cost,value,sprite,unblockable,effects);

}

ecs::entity_t Factory::createDropDetector(Vector2D pos)
{
	return ecs::entity_t();
}

ecs::entity_t Factory::createHand()
{
	if (cardFactory == nullptr) {
		throw "no existe cardFactory";
	}

	return cardFactory->createHand();
}

void Factory::createDeck()
{
	if (cardFactory == nullptr) {
		throw "no existe cardFactory";
	}

	return cardFactory->createDeck();
}

void Factory::createDeckJ2()
{
	if (cardFactory == nullptr) {
		throw "no existe cardFactory";
	}

	return cardFactory->createDeckJ2();
}

ecs::entity_t Factory::createBoard()
{
	return boardFactory->createBoard();
}

ecs::entity_t Factory::createVisual_EndTurnButton(int posX, int posY)
{
	return matchStateUIFactory->createVisual_NextTurnButton(posX, posY);
}


ecs::entity_t Factory::createVisual_ActionPointsCounter(int posX, int posY)
{
	return matchStateUIFactory->createVisual_ActionPointsCounter(posX, posY);
}

ecs::entity_t Factory::createVisual_ScoreCounter(int posX, int posY, SDL_Color color)
{
	return matchStateUIFactory->createVisual_ScoreCounter(posX, posY, color);
}


ecs::entity_t Factory::createVisual_PlayerTurnIndicator(int posX, int posY)
{
	return matchStateUIFactory->createVisual_PlayerTurnIndicator(posX, posY);
}

ecs::entity_t Factory::createVisual_BackgroundBlackBox(int posX, int posY, float xPixelsSize, float yPixelsSize)
{
	return  matchStateUIFactory->createVisual_BackgroundBlackBox(posX, posY, xPixelsSize, yPixelsSize);
}
