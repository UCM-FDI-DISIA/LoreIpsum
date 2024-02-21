#include "CardStateManager.h"

CardStateManager::CardStateManager()
{
	currentState = ON_DECK;
}

void CardStateManager::setState(CardState newState)
{
	currentState = newState;
}
