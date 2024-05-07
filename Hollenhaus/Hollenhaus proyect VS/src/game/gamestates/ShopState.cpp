#include <../pchs/pch.h>

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
#include "../../sdlutils/RandomNumberGenerator.h"
// Factorias:
#include "../factories/Factory.h"
#include "../factories/FakeCardFactory_v0.h"
#include "game/components/Clickable.h"

ShopState::ShopState() : rand_(sdlutils().rand())
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

	// llamada al input
	ih().insertFunction(ih().PAUSEKEY_DOWN, [this] { onPauseSH(); });

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
	//ecs::entity_t shopText = Instantiate(Vector2D(400, 30));
	//shopText->addComponent<TextComponent>("TIENDA", "8bit_size_40", SDL_Color({ 255, 255, 255, 255 }), 350,
	//	Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	//shopText->setLayer(1);

	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("fondoTienda");
	fondo->getComponent<Transform>()->setGlobalScale(0.475f, 0.475f);
	fondo->setLayer(0);

	//-----MONEDAS:
	createCoins();

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
		exitButton->addComponent<Clickable>("boton_flecha", true);

	//------Sonido de la tienda:
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("shoptheme").play(-1);
	sdl.soundEffects().at("shoptheme").setChannelVolume(10);
}

void ShopState::onExit()
{
	std::cout << "\nEXIT SHOP.";

	// se desuscribe al evento
	ih().clearFunction(ih().PAUSEKEY_UP, [this] { onPauseSH(); });

	saveData();
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("shoptheme").pauseChannel();
	GameStateMachine::instance()->getMngr()->Free();

	delete factory;
}

void ShopState::onPauseSH()
{
	SetLastState(3);
	GameStateMachine::instance()->setState(17);
}

ecs::entity_t ShopState::createCard(int id, Vector2D pos)
{
	// Hace LA carta
	auto card = sdlutils().cards().at(std::to_string(id));
	ecs::entity_t ent = factory->createFakeCard(id, pos, card.cost(), card.value(), card.sprite(), card.unblockable(), card.effects());
	return ent;

}

#pragma region Metodos de la gestion de la compra

void ShopState::cardSelected(int prize)
{
	shine(prize / COIN_VALUE);
}

void ShopState::deSelected()
{
	if (mngr().getEntities(ecs::grp::COINS).capacity() == 0)
	{
	for (int i = 0; i < 8; i++)
	{
		mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>()->setTexture("moneda");
	}
	updateCoins();
	}
}

void ShopState::shine(int nCoins)
{
	for (int i = 0; i < nCoins; i++)
	{
		mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>()->setTexture("monedaIlu");
	}
}
#pragma endregion

#pragma region Metodos de creacion y gestion de las monedas

void ShopState::createCoins()
{
	int playerMoney = getMoney();
	int coins = playerMoney / COIN_VALUE;
	int nextX, nextY;

	for (int i = 0; i < coins; i++) {
		nextX = rand_.nextInt(MIN_X_POS, MAX_X_POS + 1);
		nextY = rand_.nextInt(MIN_Y_POS, MAX_Y_POS + 1);
		createCoin(nextX, nextY);
	}
}

ecs::entity_t ShopState::createCoin(int x, int y)
{
	ecs::entity_t coin = Instantiate(ecs::grp::COINS);
	coin->addComponent<Transform>();
	Vector2D coinPos(x, y);
	coin->getComponent<Transform>()->setGlobalPos(coinPos);
	coin->getComponent<Transform>()->setGlobalScale(0.25f, 0.25f);
	coin->addComponent<SpriteRenderer>("moneda");
	coin->setLayer(4);

	return coin;
}

void ShopState::updateCoins()
{
	int playerMoney = getMoney();
	int coins = playerMoney / COIN_VALUE;
	for (int i = 0; i < mngr().getEntities(ecs::grp::COINS).size(); i++)
	{
		if (i < coins)
		{
			showCoin(mngr().getEntities(ecs::grp::COINS)[i]);
		}
		else
		{
			hideCoin(mngr().getEntities(ecs::grp::COINS)[i]);
		}
	}
}

void ShopState::showCoin(ecs::entity_t coinToShow)
{
	int x = rand_.nextInt(MIN_X_POS, MAX_X_POS + 1);
	int y = rand_.nextInt(MIN_Y_POS, MAX_Y_POS + 1);
	coinToShow->getComponent<Transform>()->setGlobalPos(x, y);
}

void ShopState::hideCoin(ecs::entity_t coinToHide)
{
	coinToHide->getComponent<Transform>()->setGlobalPos(1000, 1000); // La tira para fuera para que no se vea jsjs.
}
#pragma endregion

#pragma region Manager de compra

void ShopState::setDecisionManager()
{
	manager = Instantiate();

	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::DECISION_MANAGER, manager);
	manager->addComponent<DecisionComponent>();
}
#pragma endregion
