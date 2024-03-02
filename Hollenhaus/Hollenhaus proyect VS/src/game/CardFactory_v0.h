#pragma once


#include "CardFactory.h"


class CardFactory_v0 : public CardFactory{

	float cardScale = 0.55f;
	
public:
	CardFactory_v0() : CardFactory() {};
	~CardFactory_v0(){};

	ecs::entity_t createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<SDLUtils::CardEffect>& effects)override ;
	
	void createHand() override;
	
	//ecs::entity_t createDropDetector(Vector2D pos = Vector2D(0,0)) ;
	//ecs::entity_t createDropDetector_v2(Vector2D pos = Vector2D(0,0)) ;

	//ecs::entity_t createBoard() ;

};
