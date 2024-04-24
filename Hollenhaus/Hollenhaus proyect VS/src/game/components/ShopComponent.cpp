#include <../pchs/pch.h>

#include "ShopComponent.h"
#include "../GameStateMachine.h"
#include "../gamestates/GameState.h"
#include "../../utils/Vector2D.h"
#include "Card.h"
#include "Button.h"
#include "../../game/components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "DecisionComponent.h"
//------CheckML.
#include"../checkML.h"
//------Factorias.
#include "../factories/Factory.h"
#include "../factories/DialogueFactory_V0.h"
#include "../factories/DecisionFactory_V0.h"

ShopComponent::ShopComponent() : shopCards(new int[CARDS_IN_SHOP] {-1, -1, -1, -1}),
shopCardsPositions(new Vector2D[CARDS_IN_SHOP]{ Vector2D(525, 80),Vector2D(660, 80) ,Vector2D(525, 200) ,Vector2D(660, 200) }),
shopCardsPrize(new int[CARDS_IN_SHOP] {0, 0, 0, 0})
//,money(800)
{}

ShopComponent::~ShopComponent()
{
	/*delete shopCards;
	delete shopCardsPositions;
	delete shopCardsPrize;*/
}

void ShopComponent::initComponent()
{
	factory = new Factory();
	factory->SetFactories(static_cast<DialogueFactory*>(new DialogueFactory_V0()));
	//factory = new Factory();
	//factory->SetFactories(static_cast<DecisionFactory_V0*>(new DecisionFactory_V0()));

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
	setTexts();

	handler = GameStateMachine::instance()->getMngr()->getHandler(ecs::hdlr::DECISION_MANAGER);
}

void ShopComponent::generateCards()
{
	//-------------------------------------------------Esto luego sera random del json demomento es el i del for.
	for (int i = 0; i < CARDS_IN_SHOP; i++)
	{
		int cardId = 20 + i;
		GameStateMachine::instance()->getCurrentState()->setShopCard(cardId);
		shopCards[i] = cardId;
		std::cout << shopCards[i] << std::endl;
	}
}

bool ShopComponent::cardIsBought(int id)
{
	bool isBought = false;
	isBought = GameStateMachine::instance()->getCurrentState()->checkCardIsInDrawer(id);
	if (!isBought)
	{
		isBought = GameStateMachine::instance()->getCurrentState()->checkCardIsInMaze(id);
	}
	return isBought;
}

void ShopComponent::showCards() {
	for (int i = 0; i < CARDS_IN_SHOP; i++)
	{
		auto card = GameStateMachine::instance()->getCurrentState()->createCard(shopCards[i], shopCardsPositions[i]);
		card->setLayer(3);
		int id = card->getComponent<Card>()->getID();
		if (!cardIsBought(id)) // Si la carta ya esta comprada entonces no debe de ser un boton pero igualmente tiene que aparecer pero oscurecida.
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

int ShopComponent::getCardPrice(int i)
{
	return shopCardsPrize[i];
}

void ShopComponent::buyCard()
{
	if (!clicked)
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
			//------Esto para confirmar la compra.
			if (money >= shopCardsPrize[index] && !cardIsBought(id))
			{
				clicked = true;
				confirmPurchase(shopCardsPrize[index], id);
			}
		}
	}
}

void ShopComponent::purchaseCard()
{
	int id = handler->getComponent<DecisionComponent>()->getCardToPurchase();
	int index = searchIndexById(id);

	GameStateMachine::instance()->getCurrentState()->addCardToDrawer(id); // Metemos la carta al cajon.

	money -= shopCardsPrize[index]; // Restamos el dinero.

	GameStateMachine::instance()->getCurrentState()->substractMoney(shopCardsPrize[index]); // Restamos el dinero en Data.

	//std::cout << "Compra." << std::endl;

	clicked = false;
	updateTexts();
	updateColors();
	GameStateMachine::instance()->getCurrentState()->deSelected();
	handler->getComponent<DecisionComponent>()->setBuying(-1);
	handler->getComponent<DecisionComponent>()->resetCardToPurchase();
}

void ShopComponent::cancelPurchase()
{
	//std::cout << "No compra." << std::endl;
	clicked = false;
	updateTexts();
	GameStateMachine::instance()->getCurrentState()->deSelected();
	handler->getComponent<DecisionComponent>()->setBuying(-1);
	handler->getComponent<DecisionComponent>()->resetCardToPurchase();
}

void ShopComponent::updateColors()
{
	for (auto c : buyableCards)
	{
		if (cardIsBought(c->getID()))
		{
			c->getEntity()->getComponent<SpriteRenderer>()->setMultiplyColor(100, 100, 100, 255);
		}
	}
}

int ShopComponent::calculatePrize(ecs::entity_t card)
{
	int prize = 0;
	prize += (card->getComponent<Card>()->getCost() * COST_PER_COST);
	prize += (card->getComponent<Card>()->getValue() * COST_PER_VALUE);
	return prize;
}

void ShopComponent::confirmPurchase(int prize, int id)
{
	GameStateMachine::instance()->getCurrentState()->cardSelected(prize);

	handler->getComponent<DecisionComponent>()->setCardToPurchase(id);
	if (shopDialogue != nullptr)
	{
		shopDialogue = factory->createDialogue("Tienda", 0, 0,
			{ sdlutils().width() / 3.0f,sdlutils().height() / 2.0f }, // Posicion.
			{ 0.3,0.1 }, // Tamanyo.
			5, // Velocidad.
			10, // Cooldown.
			this->getEntity(), // Padre.
			3,			// Capa.
			false,		// Auto.
			"8bit_size_20",	// Font.
			SDL_Color({ 0, 0, 0, 255 }), // Color.
			220, // Wrap length.
			Text::BoxPivotPoint::LeftTop,
			Text::TextAlignment::Center);
	}
}

int ShopComponent::getPlayerMoney()
{
	return money;
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
	switch (handler->getComponent<DecisionComponent>()->getBuying())
	{
	case 0:
		cancelPurchase();
		break;
	case 1:
		purchaseCard();
		break;
	default:
		break;
	}
}

void ShopComponent::setTexts()
{
	//----Dinero-----
	moneyText = Instantiate(Vector2D(40, 100));
	moneyText->addComponent<TextComponent>(std::to_string(money), "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	moneyText->setLayer(10);
	//--------Esta muy feo ya lo siento a quien mire esto :).
	//----Carta 0----
	cardPrizeText0 = Instantiate(Vector2D(shopCardsPositions[0].getX() + 30, shopCardsPositions[0].getY() + 40));
	if (!cardIsBought(shopCards[0]))
	{
		cardPrizeText0->addComponent<TextComponent>(std::to_string(shopCardsPrize[0]), "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	else {
		cardPrizeText0->addComponent<TextComponent>("vendida", "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	cardPrizeText0->setLayer(10);
	//----Carta 1----
	cardPrizeText1 = Instantiate(Vector2D(shopCardsPositions[1].getX() + 30, shopCardsPositions[1].getY() + 40));
	if (!cardIsBought(shopCards[1]))
	{
		cardPrizeText1->addComponent<TextComponent>(std::to_string(shopCardsPrize[1]), "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	else {
		cardPrizeText1->addComponent<TextComponent>("vendida", "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	cardPrizeText1->setLayer(10);
	//----Carta 2----
	cardPrizeText2 = Instantiate(Vector2D(shopCardsPositions[2].getX() + 30, shopCardsPositions[2].getY() + 40));
	if (!cardIsBought(shopCards[2]))
	{
		cardPrizeText2->addComponent<TextComponent>(std::to_string(shopCardsPrize[2]), "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	else {
		cardPrizeText2->addComponent<TextComponent>("vendida", "8bit_size_40", SDL_Color({ 255, 0, 0, 255 }), 80, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	}
	cardPrizeText2->setLayer(10);
	//----Carta 3----
	cardPrizeText3 = Instantiate(Vector2D(shopCardsPositions[3].getX() + 30, shopCardsPositions[3].getY() + 40));
	if (!cardIsBought(shopCards[3]))
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
	if (cardIsBought(shopCards[0]))
	{
		cardPrizeText0->getComponent<TextComponent>()->setTxt("vendida");
	}
	//----Carta 1----
	if (cardIsBought(shopCards[1]))
	{
		cardPrizeText1->getComponent<TextComponent>()->setTxt("vendida");
	}
	//----Carta 2----
	if (cardIsBought(shopCards[2]))
	{
		cardPrizeText2->getComponent<TextComponent>()->setTxt("vendida");
	}
	//----Carta 3----
	if (cardIsBought(shopCards[3]))
	{
		cardPrizeText3->getComponent<TextComponent>()->setTxt("vendida");
	}
}


