#include "pch.h"
#include "ShopState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/ShineComponent.h"
#include "../components/ShopComponent.h"
#include "../components/NPC.h"
#include "../components/shopComponent.h"
#include "../GameStateMachine.h"
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
	//fondo->getComponent<Transform>()->getRelativeScale().set(5.0f, 5.0f);
	fondo->setLayer(0);

	//-----estanteria
	/*
	ecs::entity_t estanteria = Instantiate();
	estanteria->addComponent<Transform>();
	estanteria->addComponent<SpriteRenderer>("estanteria");
	Vector2D estanteriaPos(350, 80);
	estanteria->getComponent<Transform>()->setGlobalPos(estanteriaPos);
	estanteria->getComponent<Transform>()->setGlobalScale(1.5f, 1.5f);
	//estanteria->getComponent<Transform>()->getRelativeScale().set(1.5f, 1.5f);
	estanteria->setLayer(1);
	
	*/
	
	//-----MONEDAS
	createCoin(400, 500);
	createCoin(420, 540);
	createCoin(380, 525);
	createCoin(480, 500);
	createCoin(500, 540);
	createCoin(570, 530);
	createCoin(570, 500);
	updateCoinsOnTable(shopManager);

	//-----Cartas sobre la estanteria
	//carta1
	ecs::entity_t carta1 = Instantiate();
	carta1->addComponent<Transform>();
	carta1->addComponent<BoxCollider>();
	carta1->addComponent<SpriteRenderer>("card");
	carta1->addComponent<ShineComponent>();
	
	makeCoinShine(0, carta1, shopManager);

	Vector2D card1Pos(525, 80);
	carta1->getComponent<Transform>()->setGlobalPos(card1Pos);
	carta1->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	//carta1->getComponent<Transform>()->getRelativeScale().set(0.6f, 0.6f);
	carta1->setLayer(2);
	
	//carta2
	ecs::entity_t carta2 = Instantiate();
	carta2->addComponent<Transform>();
	carta2->addComponent<BoxCollider>();
	carta2->addComponent<SpriteRenderer>("card");
	carta2->addComponent<ShineComponent>();

	makeCoinShine(1, carta2, shopManager);

	Vector2D card2Pos(660, 200);
	carta2->getComponent<Transform>()->setGlobalPos(card2Pos);
	carta2->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	//carta2->getComponent<Transform>()->getRelativeScale().set(0.6f, 0.6f);
	carta2->setLayer(2);
	
	//carta3
	ecs::entity_t carta3 = Instantiate();
	carta3->addComponent<Transform>();
	carta3->addComponent<BoxCollider>();
	carta3->addComponent<SpriteRenderer>("card");
	carta3->addComponent<ShineComponent>();

	makeCoinShine(2, carta3, shopManager);

	Vector2D card3Pos(525, 200);
	carta3->getComponent<Transform>()->setGlobalPos(card3Pos);
	carta3->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	//carta3->getComponent<Transform>()->getRelativeScale().set(0.6f, 0.6f);
	carta3->setLayer(2);
	
	//carta4
	ecs::entity_t carta4 = Instantiate();
	carta4->addComponent<Transform>();
	carta4->addComponent<BoxCollider>();
	carta4->addComponent<SpriteRenderer>("card");
	carta4->addComponent<ShineComponent>();

	makeCoinShine(3, carta4, shopManager);

	Vector2D card4Pos(660, 80);
	carta4->getComponent<Transform>()->setGlobalPos(card4Pos);
	carta4->getComponent<Transform>()->setGlobalScale(0.6f, 0.6f);
	//carta4->getComponent<Transform>()->getRelativeScale().set(0.6f, 0.6f);
	carta4->setLayer(2);
	/*
	//tendero
	ecs::entity_t tendero = Instantiate();
	tendero->addComponent<Transform>();
	tendero->addComponent<SpriteRenderer>("hombre");
	Vector2D tenderoPos(100, 100);
	tendero->getComponent<Transform>()->setGlobalPos(tenderoPos);
	tendero->getComponent<Transform>()->setGlobalScale(3.0f, 3.0f);
	//tendero->getComponent<Transform>()->getRelativeScale().set(3.0f, 3.0f);
	tendero->setLayer(1);
	
	
	//mostrador
	ecs::entity_t mostrador = Instantiate();
	mostrador->addComponent<Transform>();
	mostrador->addComponent<SpriteRenderer>("mostrador");
	Vector2D mostradorPos(0, 400);
	mostrador->getComponent<Transform>()->setGlobalPos(mostradorPos);
	mostrador->getComponent<Transform>()->setGlobalScale(2.0f, 2.0f);
	//mostrador->getComponent<Transform>()->getRelativeScale().set(2.0f, 2.0f);
	mostrador->setLayer(3);*/
	


	//------Boton para volver:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(1); // Lleva a la ciudad (1).
	exit->setLayer(1);


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
	//coin7->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	coin->setLayer(4);

	return coin;
}

void ShopState::showCoin(ecs::entity_t coinToShow)
{
	coinToShow->addComponent<SpriteRenderer>("moneda");
}

void ShopState::makeCoinShine(int cardIndex, ecs::entity_t card, ecs::entity_t shopMngr)
{
	int k = shopMngr->getComponent<ShopComponent>()->getCardPrice(cardIndex);

	int nCoins = k / 100, i = 0;
	while (i < nCoins) {
		if (mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>() != nullptr) {
			card->getComponent<ShineComponent>()->addEnt(mngr().getEntities(ecs::grp::COINS)[i]->getComponent<SpriteRenderer>(), "monedaIlu");
		}
		i++;
	}
}

void ShopState::updateCoinsOnTable(ecs::entity_t shopMngr)
{
	int a = shopMngr->getComponent<ShopComponent>()->getPlayerMoney();
	int money = a / 100;
	for (int i = 0; i < money; i++) {
		showCoin(mngr().getEntities(ecs::grp::COINS)[i]);
	}
}
