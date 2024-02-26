#pragma once

#include "Entity.h"
#include "../utils/Vector2D.h"

class BoardFactory;
class CardFactory;
class HandFactory;

class Factory
{
public:

	Factory(BoardFactory* bf, CardFactory* cf, HandFactory* hf) :
		boardFactory(bf),
		cardFactory(cf),
		handFactory(hf)
	{}
	Factory(BoardFactory* bf) :
		boardFactory(bf),
		cardFactory(nullptr),
		handFactory(nullptr)
	{}
	Factory(CardFactory* cf) :
		boardFactory(nullptr),
		cardFactory(cf),
		handFactory(nullptr)
	{}
	Factory(HandFactory* hf) :
		boardFactory(nullptr),
		cardFactory(nullptr),
		handFactory(hf)
	{}

	virtual ecs::entity_t createCard(Vector2D pos) {};

	virtual ecs::entity_t createDropDetector(Vector2D pos) {};

	virtual void createHand() {};
	virtual void createBoard() {};

public:
	BoardFactory* boardFactory;
	CardFactory* cardFactory;
	HandFactory* handFactory;
};

