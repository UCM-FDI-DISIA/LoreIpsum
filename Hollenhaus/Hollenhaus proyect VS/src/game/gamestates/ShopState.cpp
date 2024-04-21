#include "pch.h"
#include "ShopState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/ShineComponent.h"
#include "../components/ShopComponent.h"
#include "../components/NPC.h"
#include "../components/shopComponent.h"
#include "../GameStateMachine.h"
#include "../components/Button.h"
#include "../components/DecisionComponent.h"
// Factorias:
#include "../factories/Factory.h"
#include "../factories/FakeCardFactory_v0.h"

ShopState::ShopState()
{
	TuVieja("Loading ShopState");
}

void ShopState::update()
{
	GameState::update();
}

void ShopState::render() const
{
	GameState::render();
}

void ShopState::refresh()
{
	GameState::refresh();
}

void ShopState::onEnter()
{
	std::cout << "\nENTER SHOP.";

	// ---- CARDS ----
	factory = new Factory();
	factory->SetFactories(static_cast<FakeCardFactory*>(new FakeCardFactory_v0()));

	setDecisionManager();

	//COSAS QUE HAY EN CADA CAPA:
	//---layer 0
	// -fondo
	//
	//---layer 1
	// -boton de volver
	// -texto de la tienda
	// -estanteria
	// -tendero
	//
	//---layer 2
	// -cartas
	//
	//---layer 3
	// -mostrador
	// 
	//---layer 4
	// -monedas

	//------Manager de la tienda:
	ecs::entity_t shopManager = Instantiate();
	shopManager->addComponent<Transform>();
	shopManager->addComponent<ShopComponent>();
	shopManager->setLayer(1);

	//------Texto de la tienda:
	ecs::entity_t shopText = Instantiate(Vector2D(400, 30));
	shopText->addComponent<TextComponent>("TIENDA", "8bit_size_40", SDL_Color({ 255, 255, 255, 255 }), 350,
		Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	shopText->setLayer(1);

	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("fondoTienda");
	fondo->getComponent<Transform>()->setGlobalScale(0.475f, 0.475f);
	fondo->setLayer(0);

	//-----MONEDAS:
	posX.push_back(400); posY.push_back(500);
	posX.push_back(420); posY.push_back(540);
	posX.push_back(380); posY.push_back(525);
	posX.push_back(480); posY.push_back(500);
	posX.push_back(500); posY.push_back(540);
	posX.push_back(570); posY.push_back(530);
	posX.push_back(570); posY.push_back(500);
	posX.push_back(590); posY.push_back(550);
	posX.push_back(650); posY.push_back(555);

	int a = getMoney();
	int money = a / 100;

	for (int i = 0; i < money; i++) {
		createCoin(posX[i], posY[i]);
	}

	updateCoinsOnTable();

	//------CARTAS:
	//----Carta1:
	ecs::entity_t carta1 = Instantiate();
	carta1->addComponent<Transform>();
	carta1->addComponent<BoxCollider>();
	carta1->addComponent<SpriteRenderer>("card");
	carta1->addComponent<ShineComponent>();

	Vector2D card1Pos(525, 80);
	carta1->getComponent<Transform>()->setGlobalPos(card1Pos);
	carta1->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	carta1->setLayer(2);

	//----Carta2:
	ecs::entity_t carta2 = Instantiate();
	carta2->addComponent<Transform>();
	carta2->addComponent<BoxCollider>();
	carta2->addComponent<SpriteRenderer>("card");
	carta2->addComponent<ShineComponent>();

	Vector2D card2Pos(660, 80);
	carta2->getComponent<Transform>()->setGlobalPos(card2Pos);
	carta2->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	carta2->setLayer(2);

	//----Carta3:
	ecs::entity_t carta3 = Instantiate();
	carta3->addComponent<Transform>();
	carta3->addComponent<BoxCollider>();
	carta3->addComponent<SpriteRenderer>("card");
	carta3->addComponent<ShineComponent>();

	Vector2D card3Pos(525, 200);
	carta3->getComponent<Transform>()->setGlobalPos(card3Pos);
	carta3->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	carta3->setLayer(2);

	//----Carta4:
	ecs::entity_t carta4 = Instantiate();
	carta4->addComponent<Transform>();
	carta4->addComponent<BoxCollider>();
	carta4->addComponent<SpriteRenderer>("card");
	carta4->addComponent<ShineComponent>();

	Vector2D card4Pos(660, 200);
	carta4->getComponent<Transform>()->setGlobalPos(card4Pos);
	carta4->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	carta4->setLayer(2);



	//------Boton para volver:
	ecs::entity_t exitButton = Instantiate(Vector2D(10, 10));
	exitButton->addComponent<Transform>();
	exitButton->addComponent<SpriteRenderer>("boton_flecha");
	exitButton->addComponent<BoxCollider>();
	exitButton->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exitButton->addComponent<Button>();
	exitButton->getComponent<Button>()->connectToButton([this] {GameStateMachine::instance()->setState(1);});


	

	//------Sonido de la tienda:
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("shoptheme").play(-1);
	sdl.soundEffects().at("shoptheme").setChannelVolume(10);
}

void ShopState::onExit()
{
	std::cout << "\nEXIT SHOP.";

	saveData();
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("shoptheme").pauseChannel();
	GameStateMachine::instance()->getMngr()->Free();
}

void ShopState::cardSelected(int prize)
{
	shine(prize / COIN_VALUE);
}

void ShopState::deSelected()
{
	for (int i = 0; i < 8; i++)
	{
		mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>()->setTexture("moneda");
	}
	updateCoinsOnTable();
}

void ShopState::shine(int nCoins)
{
	for (int i = 0; i < nCoins; i++)
	{
		mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>()->setTexture("monedaIlu");
	}
}

ecs::entity_t ShopState::createCard(int id, Vector2D pos)
{
	// Hace LA carta
	auto card = sdlutils().cards().at(std::to_string(id));
	ecs::entity_t ent = factory->createFakeCard(id, pos, card.cost(), card.value(), card.sprite(), card.unblockable(), card.effects());
	return ent;

}

ecs::entity_t ShopState::createCoin(int x, int y)
{
	ecs::entity_t coin = Instantiate(ecs::grp::COINS);
	coin->addComponent<Transform>();
	Vector2D coinPos(x, y);
	coin->getComponent<Transform>()->setGlobalPos(coinPos);
	coin->getComponent<Transform>()->setGlobalScale(0.25f, 0.25f);
	coin->setLayer(4);

	return coin;
}

void ShopState::showCoin(ecs::entity_t coinToShow)
{
	coinToShow->addComponent<SpriteRenderer>("moneda");
}

/*void ShopState::makeCoinShine(int cardIndex, ecs::entity_t card, ecs::entity_t shopMngr)
{
	int k = shopMngr->getComponent<ShopComponent>()->getCardPrice(cardIndex);

	int nCoins = k / 100, i = 0;

	while (i < nCoins) {
		if (mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>() != nullptr) {
			card->getComponent<ShineComponent>()->addEnt(mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>(), "monedaIlu");
			i++;
		}
	}
}*/

void ShopState::updateCoinsOnTable()
{
	int a = getMoney();
	int money = a / 100;
	for (int i = 0; i < money; i++) {
		showCoin(mngr().getEntities(ecs::grp::COINS)[i]);
	}
}

void ShopState::setDecisionManager()
{
	manager = Instantiate();

	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::DECISION_MANAGER, manager);
	manager->addComponent<DecisionComponent>();
}
