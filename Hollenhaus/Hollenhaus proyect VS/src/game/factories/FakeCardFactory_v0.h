#pragma once 

//Checkml
#include <game/checkML.h>

#include "FakeCardFactory.h"

class Card;

class FakeCardFactory_v0 : public FakeCardFactory
{
private:
	float cardScale = 0.55f;

	void addEffectsImages(ecs::entity_t card, std::vector<JsonData::CardEffect>& effects);
	void addValueCostTexts(ecs::entity_t card, int vale, int cost);
	void addEffects(Card* cardComp, std::vector<JsonData::CardEffect>& effects);

public:

	//---- Constructora/Destructora ----
	FakeCardFactory_v0() : FakeCardFactory(){}
	virtual ~FakeCardFactory_v0(){}

	// Crea una carta de pega
	ecs::entity_t createFakeCard(int id, Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<JsonData::CardEffect>& effects) override;

};

