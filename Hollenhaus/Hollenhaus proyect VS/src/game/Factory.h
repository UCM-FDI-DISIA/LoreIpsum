#pragma once

#include "Entity.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"

class BoardFactory;
class CardFactory;
class HandFactory;

class Factory
{
public:


	
#pragma region Templates contructoras
	/*
		Si se añade un nuevo tipo de factory para objetos en especifico,
		hay que meter una nueva variable de ese tipo en esta clase y crear una
		nueva constructora con template como las que están ya hechas
	*/

	template<typename T, typename ...Ts>
	Factory(BoardFactory* bf, Ts &&... args) {
		boardFactory = bf;
		Factory(std::forward<Ts>(args)...);
	}

	template<typename T, typename ...Ts>
	Factory(CardFactory* bf, Ts &&... args) {
		boardFactory = bf;
		Factory(std::forward<Ts>(args)...);
	}

	template<typename T, typename ...Ts>
	Factory(HandFactory* bf, Ts &&... args) {
		boardFactory = bf;
		Factory(std::forward<Ts>(args)...);
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

