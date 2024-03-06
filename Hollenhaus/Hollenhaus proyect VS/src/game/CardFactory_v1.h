#pragma once
#include "CardFactory.h"
class CardFactory_v1 :
    public CardFactory
{
public:
	CardFactory_v1() : CardFactory() {};
	~CardFactory_v1() {};

	ecs::entity_t createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<SDLUtils::CardEffect>& effects)override;
	
	ecs::entity_t createHand() override;
	void createDeck() override;
	void createDeckJ2() override;
	//ecs::entity_t createDropDetector(Vector2D pos = Vector2D(0,0)) ;
	//ecs::entity_t createDropDetector_v2(Vector2D pos = Vector2D(0,0)) ;

	//ecs::entity_t createBoard() ;

private:
	float cardScale = 0.55f;
	int cardsOnDeck = 9;
	ecs::entity_t createHandJ2();

	void addEffectsImages(ecs::entity_t card, std::vector<SDLUtils::CardEffect>& effects);
	void addValueCostTexts(ecs::entity_t card, int vale, int cost);

	void addDeckImage(int initX, int initY);
};

