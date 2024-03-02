#pragma once


#include <vector>
#include "../sdlutils/SDLUtils.h"

class Vector2D;



class CardFactory_v0 {

	float cardScale = 0.55f;
	
public:
	ecs::entity_t createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<SDLUtils::CardEffect>& effects) ;
	
	void createHand() ;
	
	//ecs::entity_t createDropDetector(Vector2D pos = Vector2D(0,0)) ;
	//ecs::entity_t createDropDetector_v2(Vector2D pos = Vector2D(0,0)) ;

	//ecs::entity_t createBoard() ;

};
