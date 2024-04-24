#include <../pchs/pch.h>

#include "CardStateManager.h"
#include "../HandComponent.h"
#include "Manager.h"

CardStateManager::CardStateManager()
{
	currentState = Cards::ON_DECK;
}

void CardStateManager::setState(Cards::State newState)
{
	currentState = newState;
}

void CardStateManager::putOnBoard()
{
	setState(Cards::ON_CELL);

	//quitar la carta de la mano
	ent_->getComponent<Transform>()->getParent()->getEntity()
	    ->getComponent<HandComponent>()->removeCard(ent_);
}
