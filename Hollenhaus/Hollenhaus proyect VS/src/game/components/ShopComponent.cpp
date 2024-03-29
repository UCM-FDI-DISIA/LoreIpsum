#include "pch.h"
#include "ShopComponent.h"
#include "../GameStateMachine.h"
#include "../gamestates/GameState.h"
#include "../../utils/Vector2D.h"

ShopComponent::ShopComponent() : shopCards(new int[CARDS_IN_SHOP] {-1, -1, -1, -1}), shopCardsPositions(new Vector2D[CARDS_IN_SHOP]{ Vector2D(100,100),Vector2D(100,200) ,Vector2D(200,100) ,Vector2D(200,200) })
{}

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
		for (int i = 0; i < CARDS_IN_SHOP; i++)
		{
			shopCards[i] = GameStateMachine::instance()->getCurrentState()->getShopCardById(i);
			std::cout << shopCards[i] << std::endl;
		}
	}

	showCards();
}

void ShopComponent::generateCards()
{
	//-------------------------------------------------Esto luego sera random del json demomento es el i del for.
	for (int i = 0; i < CARDS_IN_SHOP; i++)
	{
		GameStateMachine::instance()->getCurrentState()->setShopCard(i);
		shopCards[i] = i;
		std::cout << shopCards[i] << std::endl;
	}
}

bool ShopComponent::checkCardIsBought(int id)
{
	return GameStateMachine::instance()->getCurrentState()->checkCardIsInDrawer(id);
}

void ShopComponent::showCards() {
	for (int i = 0; i < CARDS_IN_SHOP; i++)
	{
		/*if (shopCards[i] == 2)
		{
			std::cout << "Pruebita para ver si las que ya estan no las pone en pantalla." << std::endl;
			GameStateMachine::instance()->getCurrentState()->addCardToDrawer(shopCards[i]);
		}*/
		if (!checkCardIsBought(i))
		{
			std::cout << "Mostrar carta." << std::endl;
			GameStateMachine::instance()->getCurrentState()->createCard(shopCards[i], shopCardsPositions[i]);
		}
	}
}