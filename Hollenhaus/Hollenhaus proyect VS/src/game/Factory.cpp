#include "Factory.h"


ecs::entity_t Factory::createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<SDLUtils::CardEffect>& effects)
{
	if (cardFactory == nullptr) {
		throw "no existe cardFactory";
	}

	return ecs::entity_t();

}

ecs::entity_t Factory::createDropDetector(Vector2D pos)
{
	return ecs::entity_t();
}

void Factory::createHand()
{
}

ecs::entity_t Factory::createBoard()
{
	return ecs::entity_t();
}
