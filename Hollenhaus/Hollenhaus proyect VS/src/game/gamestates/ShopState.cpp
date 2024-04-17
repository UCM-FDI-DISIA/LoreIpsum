#include "pch.h"
#include "ShopState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/ShineComponent.h"
#include "../components/NPC.h"
#include "../components/ShopComponent.h"

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

	// llamada al input
	ih().insertFunction(ih().PAUSEKEY_DOWN, [this] { onPauseSH(); });

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
	estanteria->setLayer(1);*/

	//moneda1
	ecs::entity_t coin1 = Instantiate();
	coin1->addComponent<Transform>();
	coin1->addComponent<SpriteRenderer>("moneda");
	Vector2D coin1Pos(400, 500);
	coin1->getComponent<Transform>()->setGlobalPos(coin1Pos);
	coin1->getComponent<Transform>()->setGlobalScale(0.25f, 0.25f);
	//coin1->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	coin1->setLayer(4);
	
	//moneda2
	ecs::entity_t coin2 = Instantiate();
	coin2->addComponent<Transform>();
	coin2->addComponent<SpriteRenderer>("moneda");
	Vector2D coin2Pos(420, 540);
	coin2->getComponent<Transform>()->setGlobalPos(coin2Pos);
	coin2->getComponent<Transform>()->setGlobalScale(0.25f, 0.25f);
	//coin2->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	coin2->setLayer(4);
	
	//moneda3
	ecs::entity_t coin3 = Instantiate();
	coin3->addComponent<Transform>();
	coin3->addComponent<SpriteRenderer>("moneda");
	Vector2D coin3Pos(380, 525);
	coin3->getComponent<Transform>()->setGlobalPos(coin3Pos);
	coin3->getComponent<Transform>()->setGlobalScale(0.25f, 0.25f);
	//coin3->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	coin3->setLayer(4);
	
	//moneda4
	ecs::entity_t coin4 = Instantiate();
	coin4->addComponent<Transform>();
	coin4->addComponent<SpriteRenderer>("moneda");
	Vector2D coin4Pos(480, 500);
	coin4->getComponent<Transform>()->setGlobalPos(coin4Pos);
	coin4->getComponent<Transform>()->setGlobalScale(0.25f, 0.25f);
	//coin4->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	coin4->setLayer(4);
	
	//moneda5
	ecs::entity_t coin5 = Instantiate();
	coin5->addComponent<Transform>();
	coin5->addComponent<SpriteRenderer>("moneda");
	Vector2D coin5Pos(500, 540);
	coin5->getComponent<Transform>()->setGlobalPos(coin5Pos);
	coin5->getComponent<Transform>()->setGlobalScale(0.25f, 0.25f);
	//coin5->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	coin5->setLayer(4);
	
	//moneda6
	ecs::entity_t coin6 = Instantiate();
	coin6->addComponent<Transform>();
	coin6->addComponent<SpriteRenderer>("moneda");
	Vector2D coin6Pos(570, 530);
	coin6->getComponent<Transform>()->setGlobalPos(coin6Pos);
	coin6->getComponent<Transform>()->setGlobalScale(0.25f, 0.25f);
	//coin6->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	coin6->setLayer(4);
	
	//moneda7
	ecs::entity_t coin7 = Instantiate();
	coin7->addComponent<Transform>();
	coin7->addComponent<SpriteRenderer>("moneda");
	Vector2D coin7Pos(570, 500);
	coin7->getComponent<Transform>()->setGlobalPos(coin7Pos);
	coin7->getComponent<Transform>()->setGlobalScale(0.25f, 0.25f);
	//coin7->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	coin7->setLayer(4);

	//-----Cartas sobre la estanteria
	//carta1
	ecs::entity_t carta1 = Instantiate();
	carta1->addComponent<Transform>();
	carta1->addComponent<BoxCollider>();
	carta1->addComponent<SpriteRenderer>("card");
	carta1->addComponent<ShineComponent>();
	carta1->getComponent<ShineComponent>()->addEnt(coin7->getComponent<SpriteRenderer>(), "monedaIlu");
	carta1->getComponent<ShineComponent>()->addEnt(coin6->getComponent<SpriteRenderer>(), "monedaIlu");
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
	carta2->getComponent<ShineComponent>()->addEnt(coin3->getComponent<SpriteRenderer>(), "monedaIlu");
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
	carta3->getComponent<ShineComponent>()->addEnt(coin5->getComponent<SpriteRenderer>(), "monedaIlu");
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
	carta4->getComponent<ShineComponent>()->addEnt(coin1->getComponent<SpriteRenderer>(), "monedaIlu");
	carta4->getComponent<ShineComponent>()->addEnt(coin2->getComponent<SpriteRenderer>(), "monedaIlu");
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

	//------Manager de la tienda:
	ecs::entity_t shopManager = Instantiate();
	shopManager->addComponent<Transform>();
	shopManager->addComponent<ShopComponent>();
	shopManager->setLayer(1);

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
