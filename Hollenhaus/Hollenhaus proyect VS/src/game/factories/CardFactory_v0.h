#pragma once


#include "CardFactory.h"


class CardFactory_v0 : public CardFactory
{
	float cardScale = 0.55f;
	int cardsOnHand = 8;

public:
	CardFactory_v0() : CardFactory()
	{
	};

	~CardFactory_v0() override
	{
	};

	ecs::entity_t createCard(int id, Vector2D pos, int cost, int value, std::string& sprite, bool unblockable,
	                         std::vector<JsonData::CardEffect>& effects, bool bocabajo) override;

	ecs::entity_t createHand() override;
	ecs::entity_t createDeck() override { return nullptr; };
	ecs::entity_t createDeckJ2() override { return nullptr; };
	//ecs::entity_t createDropDetector(Vector2D pos = Vector2D(0,0)) ;
	//ecs::entity_t createDropDetector_v2(Vector2D pos = Vector2D(0,0)) ;

	//ecs::entity_t createBoard() ;

private:
	void addEffectsImages(ecs::entity_t card, std::vector<JsonData::CardEffect>& effects);

	void addValueCostTexts(ecs::entity_t card, int vale, int cost);
};
