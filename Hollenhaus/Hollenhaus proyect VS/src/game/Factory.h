#pragma once

#include "Entity.h"
#include "../utils/Vector2D.h"

class BoardFactory;
class CardFactory;
class HandFactory;

class Factory
{
public:


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

	Factory()
	{}


	virtual ecs::entity_t createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable) { return nullptr; };

	virtual ecs::entity_t createDropDetector(Vector2D pos) { return nullptr; };

	virtual void createHand() {};
	virtual void createBoard() {};

public:
	BoardFactory* boardFactory;
	CardFactory* cardFactory;
	HandFactory* handFactory;
};

