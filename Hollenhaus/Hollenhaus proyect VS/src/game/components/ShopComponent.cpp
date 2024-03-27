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
	if (GameStateMachine::instance()->getCurrentState()->checkDataShopCardsIsEmpty()) // Si no hay cartas de la tienda en Data entonces se tienen que generar.
	{
		generateCards();
	}
	else
	{
		//-------------------------------------Traer desde Data las cartas de la tienda.
	}


}

void ShopComponent::generateCards()
{
	//-------------------------------------------------Esto luego sera random del json demomento es el i del for.
	for (size_t i = 0; i < 4; i++)
	{
		GameStateMachine::instance()->getCurrentState()->setShopCard(i);
		//--------meterla en el array de aqui.
	}
}

bool ShopComponent::checkCardIsBought(int id)
{
	return GameStateMachine::instance()->getCurrentState()->checkCardIsInDrawer(id);
}