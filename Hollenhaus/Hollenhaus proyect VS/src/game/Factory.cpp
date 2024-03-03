#include "Factory.h"
#include "CardFactory.h"
#include "BoardFactory.h"



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

void Factory::createHand()
{
	if (cardFactory == nullptr) {
		throw "no existe cardFactory";
	}

	return cardFactory->createHand();
}

ecs::entity_t Factory::createBoard()
{
	return boardFactory->createBoard();
}
