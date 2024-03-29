#pragma once


namespace JsonData
{
	struct CardEffect;
}

class CardFactory
{

public:

	CardFactory() {};
	virtual ~CardFactory() {};

	virtual ecs::entity_t
		createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<JsonData::CardEffect>& effects) = 0;

	virtual ecs::entity_t createHand() = 0;
	virtual ecs::entity_t createDeck() = 0;
	virtual ecs::entity_t createDeckJ2() = 0;

};

