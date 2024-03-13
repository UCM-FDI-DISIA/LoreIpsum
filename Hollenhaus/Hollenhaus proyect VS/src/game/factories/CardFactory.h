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
	virtual void createDeck() = 0;
	virtual void createDeckJ2() = 0;

};

