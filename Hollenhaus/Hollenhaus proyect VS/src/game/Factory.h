#pragma once

#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"

class CardFactory;
class HandFactory;

#include "CardFactory.h"
#include "BoardFactory.h"

class Factory
{
public:


	
#pragma region Templates setFactories
	/*
		Si se añade un nuevo tipo de factory para objetos en especifico,
		hay que meter una nueva variable de ese tipo en esta clase y crear una
		sobrecarga de este metodo con template como las que están ya hechas
	*/

	
	template<typename ...Ts>
	void SetFactories(Ts &&... args){};
	

	template<typename ...Ts>
	void SetFactories(BoardFactory* bf, Ts &&... args) {
		boardFactory = bf;
		SetFactories(std::forward<Ts>(args)...);
	}

	
	template<typename ...Ts>
	void SetFactories(CardFactory* cf, Ts &&... args) {
		cardFactory =cf;
		SetFactories(std::forward<Ts>(args)...);
	}
	
		

#pragma endregion

	Factory(){};


	virtual ecs::entity_t createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<SDLUtils::CardEffect>& effects);

	virtual ecs::entity_t createDropDetector(Vector2D pos);

	virtual void createHand() ;
	virtual ecs::entity_t createBoard();

public:

	BoardFactory* boardFactory;
	CardFactory* cardFactory;
	HandFactory* handFactory;
};

