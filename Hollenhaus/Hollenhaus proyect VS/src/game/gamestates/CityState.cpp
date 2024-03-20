#include "pch.h"
#include "CityState.h"
#include "../components/basics/TextComponent.h"
#include "../components/MoveOnClick.h"
#include "../components/NPC.h"
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"

CityState::CityState()
{
	TuVieja("Loading CityState");
}
void CityState::update()
{
	GameState::update();
}
void CityState::render() const
{
	GameState::render();
}
void CityState::refresh()
{
	GameState::refresh();
}

void CityState::onEnter()
{
	std::cout << "\nENTER CITY.\n";

	//------Texto de la ciudad:
	ecs::entity_t cityText = Instantiate(Vector2D(500, 30));
	cityText->addComponent<TextComponent>("CIUDAD", "8bit_40pt", SDL_Color({ 255, 255, 255, 255 }), 350, Text::CenterCenter, Text::Center);
	cityText->setLayer(1);

	//-----Ciudad de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("ciudadcompleta");
	fondo->getComponent<SpriteRenderer>()->setMultiplyColor(0,255,255,255);
	fondo->addComponent<BoxCollider>();
	//tamanyo de ciudadcompleta.png: 5754 x 1212 
	fondo->getComponent<Transform>()->getGlobalScale().set(0.495f, 0.495f); //escalado para ciudadcompleta.png (porfi no toquetear)!!! 
	Vector2D globalPos(-1200.0f, 0); //Posición inicial de la ciudad para que se vea por el centro.
	fondo->getComponent<Transform>()->setGlobalPos(globalPos);
	//fondo->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	fondo->addComponent<MoveOnClick>();
	//fondo->getComponent<Transform>()->getGlobalScale().set(0.495f, 0.495f);
	fondo->setLayer(0);

	//------Personaje
	ecs::entity_t fantasmiko = Instantiate(Vector2D(sdlutils().width()/2 - 50, sdlutils().height() - 200));
	fantasmiko->addComponent<SpriteRenderer>("fantasma");
	fantasmiko->addComponent<BoxCollider>();
	fantasmiko->getComponent<Transform>()->setGlobalScale(Vector2D(0.15f, 0.15f));
	fantasmiko->getComponent<SpriteRenderer>()->setFlipX(true);
	fantasmiko->setLayer(1);

	//------NPCs que demomento son Caitlyns:
	//----Para entrar en la oficina.
	ecs::entity_t npc2 = Instantiate();
	npc2->addComponent<Transform>();
	npc2->addComponent<SpriteRenderer>("npc");
	npc2->addComponent<BoxCollider>();
	npc2->getComponent<Transform>()->addParent(fondo->getComponent<Transform>());
	npc2->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	Vector2D np2Pos(-100, 425);
	npc2->getComponent<Transform>()->setGlobalPos(np2Pos);
	npc2->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	npc2->addComponent<NPC>(2); // Lleva a la oficina (2).
	npc2->setLayer(2);
	//----Para entrar en la tienda.
	ecs::entity_t npc1 = Instantiate();
	npc1->addComponent<Transform>();
	npc1->addComponent<SpriteRenderer>("hombre");
	npc1->addComponent<BoxCollider>();
	npc1->getComponent<Transform>()->addParent(fondo->getComponent<Transform>());
	npc1->getComponent<Transform>()->getRelativeScale().set(1.0f, 1.0f);
	Vector2D np1Pos(800, 425);
	npc1->getComponent<Transform>()->setGlobalPos(np1Pos);
	npc1->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	npc1->addComponent<NPC>(3); // Lleva a la tienda (3).
	npc1->setLayer(2);
	//----Para empezar la batalla.
	ecs::entity_t npc3 = Instantiate();
	npc3->addComponent<Transform>();
	npc3->addComponent<SpriteRenderer>("npc");
	npc3->addComponent<BoxCollider>();
	npc3->getComponent<Transform>()->addParent(fondo->getComponent<Transform>());
	npc3->getComponent<Transform>()->getRelativeScale().set(0.25f, 0.25f);
	Vector2D npc3Pos(400, 425);
	npc3->getComponent<Transform>()->setGlobalPos(npc3Pos);
	npc3->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	npc3->addComponent<NPC>(6); // Lleva al combate (SamuState(6)).
	npc3->setLayer(2);

	//------Boton para volver al menu principal:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(0); // Lleva al menu (0).
	exit->setLayer(2);

	// referencia a sdlutils
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("citytheme").play(-1);
	sdl.soundEffects().at("citytheme").setChannelVolume(10);
}

void CityState::onExit()
{
	std::cout << "\nEXIT CITY.\n";

	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("citytheme").pauseChannel();
	GameStateMachine::instance()->getMngr()->Free();
}
