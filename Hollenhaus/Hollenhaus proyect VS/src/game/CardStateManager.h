#pragma once

#include "checkML.h"
#include "ComponentUpdate.h"

class CardStateManager : public ComponentUpdate
{


public:

	//constructora
	CardStateManager();


	enum CardState {
		ON_HAND,
		ON_HOVER,
		ON_DRAG,
		ON_CELL,
		ON_DECK
	};

	void setState(CardState newState);

	void putOnBoard();

	CardState getState() { return currentState; }

private:

	CardState currentState;


};

