#include "pch.h"
#include "ShopComponent.h"
#include "../GameStateMachine.h"
#include "../gamestates/GameState.h"

ShopComponent::ShopComponent() : shopCards(new int[4] {-1, -1, -1, -1}) {}

ShopComponent::~ShopComponent()
{
	delete shopCards;
}

void ShopComponent::initComponent()
{
	if (GameStateMachine::instance()->getCurrentState()->checkDataShopCardsIsEmpty())
	{
		generateCards();
	}


}

void ShopComponent::generateCards()
{
	//-------------------------------------------------Esto luego sera random del json demomento es el i del for.
	for (size_t i = 0; i < 4; i++)
	{
		GameStateMachine::instance()->getCurrentState()->setShopCard(i);
	}
}

bool ShopComponent::checkCardIsBought(int id)
{
	return GameStateMachine::instance()->getCurrentState()->checkCardIsInDrawer(id);
}