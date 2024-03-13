#include "pch.h"
#include "CardStateManager.h"
#include "../HandComponent.h"
#include "Manager.h"

CardStateManager::CardStateManager()
{
	currentState = ON_DECK;
}

void CardStateManager::setState(CardState newState)
{
	currentState = newState;
}

void CardStateManager::putOnBoard() {

	setState(ON_CELL);

	//quitar la carta de la mano
	ent_->getComponent<Transform>()->getParent()->getEntity()
		->getComponent<HandComponent>()->removeCard(ent_);
}