#include "pch.h"
#include "ShopComponent.h"
#include "../GameStateMachine.h"
#include "../gamestates/GameState.h"
#include "../../utils/Vector2D.h"

ShopComponent::ShopComponent() : shopCards(new int[4] {-1, -1, -1, -1}), shopCardsPositions(new Vector2D[4]{ Vector2D(2,2),Vector2D(2,2) ,Vector2D(2,2) ,Vector2D(2,2) }) {}

ShopComponent::~ShopComponent()
{
	delete shopCards;
}

void ShopComponent::initComponent()
{
	if (GameStateMachine::instance()->getCurrentState()->checkDataShopCardsIsEmpty()) // Si no hay cartas de la tienda en Data entonces se tienen que generar.
	{
		std::cout << "\nTienda genera cartas:" << std::endl;
		generateCards();
	}
	else
	{
		std::cout << "\nTienda trae cartas de Data:" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			shopCards[i] = GameStateMachine::instance()->getCurrentState()->getShopCardById(i);
			std::cout << shopCards[i];
		}
	}


}

void ShopComponent::generateCards()
{
	//-------------------------------------------------Esto luego sera random del json demomento es el i del for.
	for (int i = 0; i < 4; i++)
	{
		GameStateMachine::instance()->getCurrentState()->setShopCard(i);
		shopCards[i] = i;
		std::cout << shopCards[i];
	}
}

bool ShopComponent::checkCardIsBought(int id)
{
	return GameStateMachine::instance()->getCurrentState()->checkCardIsInDrawer(id);
}

void ShopComponent::showCards() {
	for (int i = 0; i < 4; i++)
	{
		if (!checkCardIsBought(i))
		{
			//GameStateMachine::instance()->getCurrentState()->createCard)()
		}
	}
}