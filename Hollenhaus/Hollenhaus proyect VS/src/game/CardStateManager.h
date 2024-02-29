#pragma once
#include "checkML.h"
#include "ComponentUpdate.h"

enum CardState {
	ON_HAND,
	ON_HOVER,
	ON_DRAG,
	ON_CELL,
	ON_DECK
};

class CardStateManager : public ComponentUpdate
{
	CardState currentState;

public:
	CardStateManager();

	void putOnBoard();

	/// getters
	CardState getState() const { return currentState; }

	/// setters
	void setState(CardState newState);
};

