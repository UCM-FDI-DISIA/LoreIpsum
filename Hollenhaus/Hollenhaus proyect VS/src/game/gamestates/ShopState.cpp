#include "pch.h"
#include "ShopState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/NPC.h"


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
	
	//------Texto de la tienda:
	ecs::entity_t shopText = Instantiate(Vector2D(400, 30));
	shopText->addComponent<TextComponent>("TIENDA", "8bit_40pt", SDL_Color({ 255, 255, 255, 255 }), 350, 
		Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	shopText->setLayer(1);

	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("tiendafondo");
	fondo->getComponent<Transform>()->getGlobalScale().set(0.85f, 0.85f);
	fondo->setLayer(0);

	//-----Cartas sobre la estanteria
	//carta1
	ecs::entity_t carta1 = Instantiate();
	carta1->addComponent<Transform>();
	carta1->addComponent<SpriteRenderer>("card");
	Vector2D card1Pos(515, 125);
	carta1->getComponent<Transform>()->setGlobalPos(card1Pos);
	carta1->getComponent<Transform>()->getRelativeScale().set(0.85f, 0.85f);
	carta1->setLayer(1);
	
	//carta2
	ecs::entity_t carta2 = Instantiate();
	carta2->addComponent<Transform>();
	carta2->addComponent<SpriteRenderer>("card");
	Vector2D card2Pos(650, 320);
	carta2->getComponent<Transform>()->setGlobalPos(card2Pos);
	carta2->getComponent<Transform>()->getRelativeScale().set(0.85f, 0.85f);
	carta2->setLayer(1);
	
	//carta3
	ecs::entity_t carta3 = Instantiate();
	carta3->addComponent<Transform>();
	carta3->addComponent<SpriteRenderer>("card");
	Vector2D card3Pos(515, 320);
	carta3->getComponent<Transform>()->setGlobalPos(card3Pos);
	carta3->getComponent<Transform>()->getRelativeScale().set(0.85f, 0.85f);
	carta3->setLayer(1);
	
	//carta4
	ecs::entity_t carta4 = Instantiate();
	carta4->addComponent<Transform>();
	carta4->addComponent<SpriteRenderer>("card");
	Vector2D card4Pos(650, 125);
	carta4->getComponent<Transform>()->setGlobalPos(card4Pos);
	carta4->getComponent<Transform>()->getRelativeScale().set(0.85f, 0.85f);
	carta4->setLayer(1);
	
	//tendero
	ecs::entity_t tendero = Instantiate();
	tendero->addComponent<Transform>();
	tendero->addComponent<SpriteRenderer>("hombre");
	Vector2D tenderoPos(100, 100);
	tendero->getComponent<Transform>()->setGlobalPos(tenderoPos);
	tendero->getComponent<Transform>()->getRelativeScale().set(3.0f, 3.0f);
	tendero->setLayer(1);


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

	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("shoptheme").pauseChannel();
	GameStateMachine::instance()->getMngr()->Free();
}
