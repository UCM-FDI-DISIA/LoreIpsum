#include "pch.h"
#include "ShopComponent.h"
#include "../GameStateMachine.h"
#include "../gamestates/GameState.h"
#include "../../utils/Vector2D.h"
#include "Card.h"
#include "Button.h"
#include "../../game/components/managers/Manager.h"

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

	money = GameStateMachine::instance()->getCurrentState()->getMoney();

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
		if (!checkCardIsBought(i)) // Comprueba si la carta esta comprada (en drawer).
		{
			std::cout << "Mostrar carta: " << shopCards[i] << std::endl;
			auto card = GameStateMachine::instance()->getCurrentState()->createCard(shopCards[i], shopCardsPositions[i]);

			if (card != nullptr)
			{
				card->addComponent<Button>();
				card->getComponent<Button>()->connectToButton([this] {buyCard();});
				buttons.push_back(card->getComponent<Button>());
				buyableCards.push_back(card->getComponent<Card>());
			}
		}
	}
}

void ShopComponent::buyCard()
{
	std::cout << "compra." << std::endl;
	//------Esto para buscar el boton que ha sido pulsado para acceder a la carta de ese boton.
	Button* buttonClicked = nullptr;
	for (auto b : buttons) // Recorremos la lista de botones.
	{
		if (b->getCurrentButtonState() == 2) // 2 = boton pulsado.
		{
			buttonClicked = b; // Guardamos el boton.
		}
	}

	//------Esto para guardar la carta al drawer.
	if (buttonClicked != nullptr)
	{
		auto card = buttonClicked->getEntity(); // Guardamos la carta del boton.
		//------Esto para confirmar la compra.---------------------------------------------alomejor separar en dos if por si se quiere poner dialogo de no tener dinero suficiente.
		if (/*money>=card.getPrize()&&*/confirmPurchase()) {
			if (card != nullptr)
			{
				int id = card->getComponent<Card>()->getID(); // Guardamos el id de la carta.
				GameStateMachine::instance()->getCurrentState()->addCardToDrawer(id); // Metemos la carta al cajon.
				//money-= card.getPrize();
				//GameStateMachine::instance()->getCurrentState()->changeMoney(-card.getPrize()); // Restamos el dinero.
				//------Esto para buscar dada la carta pulsada su indice en shopCards y ponerlo a -1 para que no se muestre.
				int i = 0;
				bool find = false;
				while (!find && i < CARDS_IN_SHOP)
				{
					if (id == shopCards[i])
					{
						find = true;
						i = -1;
					}
					i++;
				}


				//auto it = std::find(buyableCards.begin(), buyableCards.end(), id); // Buscamos y guardamos la carta en la lista.
				//buyableCards.erase(it); // La eliminamos.
				/*for (auto c : buyableCards)
				{
					delete c->getEntity(); //-------------------------------------------------------hay que eliminar las entidades pero da error de momento hasta que andres mire lo otro.
				}*/
				buyableCards.clear();
				buttons.clear();
				showCards(); // Para que se acutalice.
			}
		}
	}
}

bool ShopComponent::confirmPurchase()
{
	//----------------------------------------------------------preguntar a ines sobre el dialogo para confirmar.
	return true;
}