#pragma once

//Checkml
#include <game/checkML.h>

#include "CardFactory.h"
class Card;

class CardFactory_v1 :
    public CardFactory
{
public:
	CardFactory_v1() : CardFactory() {};
	~CardFactory_v1() {};

	ecs::entity_t createCard(int id, Vector2D pos, int cost, int value, std::string& sprite, 
		bool unblockable, std::vector<JsonData::CardEffect>& effects, bool bocarriba = true) override;
	
	ecs::entity_t createHand() override;
	ecs::entity_t createDeck() override;
	ecs::entity_t createDeckJ2(std::string j2) override;
	ecs::entity_t createDeckJ2Multiplayer() override;

private:
	float cardScale = 0.55f;
	int cardsOnDeck = 16;
	ecs::entity_t createHandJ2();

	void addInfo(ecs::entity_t card, int cost, int value, std::vector<JsonData::CardEffect>& effects, bool bocabajo);
	void addEffectsImages(ecs::entity_t card, std::vector<JsonData::CardEffect>& effects, bool rival = false);
	void addValueCostTexts(ecs::entity_t card, int vale, int cost);
	void addEffects(Card* cardComp, std::vector<JsonData::CardEffect>& effects);
	void addDeckImage(int initX, int initY, bool opposite = false);
	void addDeckImageChild(ecs::entity_t card);
	void addDeckShadow(int x, int y, int layer = 1);
	void addShadow(int x = 0, int y = 0, int layer = 1, Transform* parent = nullptr);
};

