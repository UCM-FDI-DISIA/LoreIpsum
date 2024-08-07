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
#include "../components/managers/TutorialShopManager.h"
#include "../TutorialManager.h"
#include "../SoundManager.h"

// Factorias:
#include "../factories/Factory.h"
#include "../factories/FakeCardFactory_v0.h"
#include "game/components/Clickable.h"

ShopState::ShopState() : rand_(sdlutils().rand())
{
	TuVieja("Loading ShopState");
	isTutorial = false;

}

ShopState::ShopState(bool a) : rand_(sdlutils().rand())
{

	isTutorial = a;
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

	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("tienda");
	fondo->getComponent<Transform>()->setGlobalScale(0.5f, 0.5f);
	fondo->setLayer(0);

	//-----MONEDAS:
	createCoins();

	//------CARTAS:
	//----Carta1:
	ecs::entity_t carta1 = Instantiate();
	carta1->addComponent<Transform>();
	carta1->addComponent<BoxCollider>();
	//carta1->addComponent<SpriteRenderer>("card");
	carta1->addComponent<ShineComponent>();

	Vector2D card1Pos(490, 120);
	carta1->getComponent<Transform>()->setGlobalPos(card1Pos);
	carta1->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	//carta1->setLayer(2);

	//----Carta2:
	ecs::entity_t carta2 = Instantiate();
	carta2->addComponent<Transform>();
	carta2->addComponent<BoxCollider>();
	//carta2->addComponent<SpriteRenderer>("card");
	carta2->addComponent<ShineComponent>();	

	Vector2D card2Pos(600, 120);
	carta2->getComponent<Transform>()->setGlobalPos(card2Pos);
	carta2->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	//carta2->setLayer(2);

	//----Carta3:
	ecs::entity_t carta3 = Instantiate();
	carta3->addComponent<Transform>();
	carta3->addComponent<BoxCollider>();
	//carta3->addComponent<SpriteRenderer>("card");
	carta3->addComponent<ShineComponent>();

	Vector2D card3Pos(490, 230);
	carta3->getComponent<Transform>()->setGlobalPos(card3Pos);
	carta3->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	//carta3->setLayer(2);

	//----Carta4:
	ecs::entity_t carta4 = Instantiate();
	carta4->addComponent<Transform>();
	carta4->addComponent<BoxCollider>();
	//carta4->addComponent<SpriteRenderer>("card");
	carta4->addComponent<ShineComponent>();

	Vector2D card4Pos(600, 230);
	carta4->getComponent<Transform>()->setGlobalPos(card4Pos);
	carta4->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	//carta4->setLayer(2);

	//------Boton para volver:
	ecs::entity_t exitButton = Instantiate(Vector2D(20, 20));
	exitButton->addComponent<Transform>();
	exitButton->addComponent<SpriteRenderer>("boton_flecha");
	exitButton->addComponent<BoxCollider>();
	exitButton->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exitButton->addComponent<Button>();
	exitButton->getComponent<Button>()->connectToButton([this] {GameStateMachine::instance()->setState(1);});
	exitButton->addComponent<Clickable>("boton_flecha", true);
	exitButton->getComponent<Transform>()->setGlobalPos(10, 10);

	//objs.push_back(exitButton);
	objs.push_back(carta1);
	objs.push_back(carta2);
	objs.push_back(carta3);
	objs.push_back(carta4);

	setTutorial();

	/// MUSICA
	auto music = SoundManager::instance();
	music->startMusic(Sounds::SHOP_M);

}

void ShopState::onExit()
{
	std::cout << "\nEXIT SHOP.";

	// se desuscribe al evento
	ih().clearFunction(ih().PAUSEKEY_UP, [this] { onPauseSH(); });

	saveData();

	auto music = SoundManager::instance();
	music->stopMusic(Sounds::SHOP_M);

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
	if (mngr().getEntities(ecs::grp::COINS).capacity() != 0)
	{
		for (int i = 0; i < mngr().getEntities(ecs::grp::COINS).size(); i++)
		{
			mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>()->setTexture("moneda_tienda");
		}
		updateCoins();
	}
}

void ShopState::shine(int nCoins)
{
	for (int i = 0; i < nCoins; i++)
	{
		mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>()->setTexture("moneda_tienda_brilli");
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
	coin->getComponent<Transform>()->setGlobalScale(0.5f, 0.5f);
	coin->addComponent<SpriteRenderer>("moneda_tienda");
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

void ShopState::setTutorial()
{
	if (isTutorial) {

		// entidad tutorial para gestionar cositas
		tutorial = Instantiate();

		prepareTutorial();

		tutorial->addComponent<TutorialManager>();
		auto manager = tutorial->addComponent<TutorialShopManager>(base, tutorial);
		GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::TUTORIAL_MANAGER, tutorial);


		tutorial->getComponent<TutorialManager>()->startTutorial();
		tutorial->getComponent<TutorialManager>()->setCurrentTutorial(Tutorials::SHOP);
		tutorial->getComponent<TutorialManager>()->setCurrentTutorialState(Tutorials::Tienda::SHOP_NONE);
		tutorial->getComponent<TutorialManager>()->setNextTutorialState(Tutorials::Tienda::SHOP_INIT);

		int a = tutorial->getComponent<TutorialManager>()->getTutorialState();

		tutorial->getComponent<TutorialShopManager>()->setObjs(objs);

	}
}

void ShopState::prepareTutorial()
{
	// base
	base = Instantiate();
	base->addComponent<Transform>();
	//base->getComponent<Transform>()->addParent(nullptr);
	//base->getComponent<Transform>()->getRelativeScale().set(0.25, 0.25);
	Vector2D pos{ 200, 200 };
	base->getComponent<Transform>()->setGlobalPos(pos);
	base->setLayer(2);
}

void ShopState::startTutorial(bool a)
{
	isTutorial = a;
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
