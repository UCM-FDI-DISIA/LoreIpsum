#include "pch.h"
#include "ShopComponent.h"
#include "../GameStateMachine.h"
#include "../gamestates/GameState.h"
#include "../../utils/Vector2D.h"
#include "Card.h"
#include "Button.h"
#include "../../game/components/managers/Manager.h"
#include "../components/basics/TextComponent.h"

ShopComponent::ShopComponent() : shopCards(new int[CARDS_IN_SHOP] {-1, -1, -1, -1}),
shopCardsPositions(new Vector2D[CARDS_IN_SHOP]{ Vector2D(525, 80),Vector2D(660, 200) ,Vector2D(525, 200) ,Vector2D(660, 80) }),
shopCardsPrize(new int[CARDS_IN_SHOP] {0, 0, 0, 0}),
money(500)
{}

ShopComponent::~ShopComponent()
{
	/*delete shopCards;
	delete shopCardsPositions;
	delete shopCardsPrize;*/
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

	//money = GameStateMachine::instance()->getCurrentState()->getMoney();

	showCards();
	//showPrizes();
	setTexts();
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

bool ShopComponent::cardIsBought(int id)
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
		auto card = GameStateMachine::instance()->getCurrentState()->createCard(shopCards[i], shopCardsPositions[i]);
		if (!cardIsBought(i)) // Si la carta ya esta comprada entonces no debe de ser un boton pero igualmente tiene que aparecer pero oscurecida.
		{
			if (card != nullptr)
			{
				card->addComponent<Button>();
				card->getComponent<Button>()->connectToButton([this] {buyCard();});
				shopCardsPrize[i] = calculatePrize(card);
				buttons.push_back(card->getComponent<Button>());
				buyableCards.push_back(card->getComponent<Card>());
			}

			std::cout << "Mostrar carta: " << shopCards[i] << " con precio: " << shopCardsPrize[i] << std::endl;
		}
		else
		{
			card->getComponent<SpriteRenderer>()->setMultiplyColor(100, 100, 100, 255); // Cambiamos el color de las ya compradas.
			std::cout << "Mostrar carta: " << shopCards[i] << " vendida." << std::endl;
		}
	}
}

void ShopComponent::buyCard()
{
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
		auto card = buttonClicked->getEntity(); // Carta pulsada.
		int id = card->getComponent<Card>()->getID(); // Id de la carta.
		int index = searchIndexById(id); // Indice de la carta en shopCards, shopCardspositions y shopCardsPrize.
		//------Esto para confirmar la compra.---------------------------------------------alomejor separar en dos if por si se quiere poner dialogo de no tener dinero suficiente.
		if (money >= shopCardsPrize[index] && confirmPurchase())
		{
			std::cout << "Compra." << std::endl;
			if (card != nullptr)
			{
				GameStateMachine::instance()->getCurrentState()->addCardToDrawer(id); // Metemos la carta al cajon.
				card->getComponent<SpriteRenderer>()->setMultiplyColor(100, 100, 100, 255); // Cambiamos el color.
				money -= shopCardsPrize[index]; // Restamos el dinero.
				GameStateMachine::instance()->getCurrentState()->changeMoney(shopCardsPrize[index]); // Restamos el dinero en Data.
				//showPrizes(); // Para que se actualicen los precios.
				updateTexts();
			}
		}
	}
}

/*void ShopComponent::showPrizes()
{
	std::string txt = "";
	for (int i = 0; i < CARDS_IN_SHOP; i++)
	{
		ecs::entity_t shopText = Instantiate(Vector2D(shopCardsPositions[i].getX() + 30, shopCardsPositions[i].getY() + 40));
		if (!cardIsBought(i)) // Sino esta vendida aparece el precio.
		{
			txt = std::to_string(shopCardsPrize[i]);
		}
		else // Sino, pone que esta vendida.
		{
			txt = "vendida";
		}
		shopText->addComponent<TextComponent>(txt, "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
		shopText->setLayer(6);
	}
}*/

int ShopComponent::calculatePrize(ecs::entity_t card)
{
	int prize = 0;
	prize += (card->getComponent<Card>()->getCost() * COST_PER_COST);
	prize += (card->getComponent<Card>()->getEffectSize() * COST_PER_EFFECTS);
	return prize;
}

bool ShopComponent::confirmPurchase()
{
	//----------------------------------------------------------preguntar a ines sobre el dialogo para confirmar.
	return true;
}

int ShopComponent::searchIndexById(int id)
{
	int i = 0;
	bool find = false;
	while (!find && i < CARDS_IN_SHOP)
	{
		if (shopCards[i] == id)
		{
			find = true;
		}
		else { i++; }
	}
	return i;
}

void ShopComponent::update()
{
	//std::cout << "Money: " << money << std::endl;
}

void ShopComponent::setTexts()
{
	//----Dinero-----
	moneyText = Instantiate(Vector2D(40, 100));
	moneyText->addComponent<TextComponent>(std::to_string(money), "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	//--------Esta muy feo ya lo siento a quien mire esto :).
	//----Carta 0----
	cardPrizeText0 = Instantiate(Vector2D(shopCardsPositions[0].getX() + 30, shopCardsPositions[0].getY() + 40));
	if (!cardIsBought(0))
	{
		cardPrizeText0->addComponent<TextComponent>(std::to_string(shopCardsPrize[0]), "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	else {
		cardPrizeText0->addComponent<TextComponent>("vendida", "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	cardPrizeText0->setLayer(10);
	//----Carta 1----
	cardPrizeText1 = Instantiate(Vector2D(shopCardsPositions[1].getX() + 30, shopCardsPositions[1].getY() + 40));
	if (!cardIsBought(1))
	{
		cardPrizeText1->addComponent<TextComponent>(std::to_string(shopCardsPrize[1]), "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	else {
		cardPrizeText1->addComponent<TextComponent>("vendida", "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	cardPrizeText1->setLayer(10);
	//----Carta 2----
	cardPrizeText2 = Instantiate(Vector2D(shopCardsPositions[2].getX() + 30, shopCardsPositions[2].getY() + 40));
	if (!cardIsBought(2))
	{
		cardPrizeText2->addComponent<TextComponent>(std::to_string(shopCardsPrize[2]), "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	else {
		cardPrizeText2->addComponent<TextComponent>("vendida", "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	cardPrizeText2->setLayer(10);
	//----Carta 3----
	cardPrizeText3 = Instantiate(Vector2D(shopCardsPositions[3].getX() + 30, shopCardsPositions[3].getY() + 40));
	if (!cardIsBought(3))
	{
		cardPrizeText3->addComponent<TextComponent>(std::to_string(shopCardsPrize[3]), "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	else {
		cardPrizeText3->addComponent<TextComponent>("vendida", "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	cardPrizeText3->setLayer(10);
}
void ShopComponent::updateTexts()
{
	//----Dinero----
	moneyText->getComponent<TextComponent>()->setTxt(std::to_string(money));
	//----Carta 0----
	if (cardIsBought(0))
	{
		cardPrizeText0->getComponent<TextComponent>()->setTxt("vendida");
	}
	//----Carta 1----
	if (cardIsBought(1))
	{
		cardPrizeText1->getComponent<TextComponent>()->setTxt("vendida");
	}
	//----Carta 2----
	if (cardIsBought(2))
	{
		cardPrizeText2->getComponent<TextComponent>()->setTxt("vendida");
	}
	//----Carta 3----
	if (cardIsBought(3))
	{
		cardPrizeText3->getComponent<TextComponent>()->setTxt("vendida");
	}
}