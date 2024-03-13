#pragma once
#include "../ComponentUpdate.h"

class CardStateManager : public ComponentUpdate
{

public:
	CardStateManager();

	void putOnBoard();

	/// getters
	Cards::State getState() const { return currentState; }

	/// setters
	void setState(Cards::State newState);

private:
	Cards::State currentState;
};

