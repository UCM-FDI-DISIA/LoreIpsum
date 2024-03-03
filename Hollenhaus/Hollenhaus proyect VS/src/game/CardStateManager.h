#pragma once
#include "checkML.h"
#include "ComponentUpdate.h"


class CardStateManager : public ComponentUpdate
{

public:
	enum CardState {
		ON_HAND,
		ON_HOVER,
		ON_DRAG,
		ON_CELL,
		ON_DECK
	};

	CardStateManager();

	void putOnBoard();

	/// getters
	CardState getState() const { return currentState; }

	/// setters
	void setState(CardState newState);

private:
	CardState currentState;
};

