#include "pch.h"
#include "Factory.h"
#include "CardFactory.h"
#include "BoardFactory.h"
#include "FakeCardFactory.h"
#include "MatchStateUIFactory.h"
#include "DialogueFactory.h"
#include "NPCFactory.h"
#include "DecisionFactory.h"


ecs::entity_t Factory::createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<JsonData::CardEffect>& effects)
{
	if (cardFactory == nullptr) {
		throw "no existe cardFactory";
	}

	return cardFactory->createCard(pos,cost,value,sprite,unblockable,effects);

}
ecs::entity_t Factory::createFakeCard(int id, Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<JsonData::CardEffect>& effects)
{
	if (fakeCardFactory == nullptr) {
		throw "no existe fakeCardFactory";
	}

	return fakeCardFactory->createFakeCard(id, pos, cost, value, sprite, unblockable, effects);

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

ecs::entity_t Factory::createVisual_BackgroundFullImage()
{
	return matchStateUIFactory->createVisual_BackgroundBoard();
}

ecs::entity_t Factory::createNPC(std::string id, std::string sprite,
	Vector2D scale, Vector2D pos, int type, int scene, int layer,
	ecs::entity_t parent)
{
	if (npcFactory == nullptr) {
		throw "no existe npcFactory";
	}

	// PLACEHOLDER
	return npcFactory->createNPC(id, sprite, scale, pos, type, scene, layer, parent);
}


ecs::entity_t Factory::createDialogue(std::string id, int convo, int node, Vector2D pos, Vector2D size,
	int speed, int cooldown, ecs::entity_t parent, int layer, std::string fontID, SDL_Color color, Uint32 wrapLenght, Text::BoxPivotPoint boxPivotPoint,
	Text::TextAlignment textAlignment)
{
	if (dialogueFactory == nullptr) {
		throw "no existe dialogueFactory";
	}

	dialogueFactory->setTextValues(fontID, color, wrapLenght, boxPivotPoint, textAlignment);
	return dialogueFactory->createDialogue(id, convo, node, pos, size, speed, cooldown, parent, layer);
	
}

void Factory::createDecision(Vector2D pos, Vector2D size, ecs::entity_t parent, int layer,
	std::string fontID, SDL_Color color, Text::BoxPivotPoint boxPivotPoint, Text::TextAlignment textAlignment)
{
	if (decisionFactory == nullptr) {
		throw "no existe decisionFactory";
	}

	decisionFactory->setTextValues(fontID, color, boxPivotPoint, textAlignment);
	decisionFactory->createPopUp(pos, size, parent, layer);
}
