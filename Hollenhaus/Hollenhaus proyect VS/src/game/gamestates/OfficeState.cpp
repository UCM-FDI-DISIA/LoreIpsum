#include "pch.h"
#include "OfficeState.h"
#include "../components/managers/Manager.h"
#include "../../sdlutils/InputHandler.h"
#include "../components/basics/TextComponent.h"

#include "../components/NPC.h"


OfficeState::OfficeState()
{
	TuVieja("Loading OfficeState");
}

void OfficeState::update()
{
	GameState::update();
}

void OfficeState::render() const
{
	GameState::render();
}

void OfficeState::refresh()
{
	GameState::refresh();
}

void OfficeState::onEnter()
{
	std::cout << "\nENTER OFFICE.\n";
	
	//------Texto de la oficina.
	ecs::entity_t officeText = Instantiate(Vector2D(210, 30));
	officeText->addComponent<TextComponent>("OFICINA", "8bit_24pt", SDL_Color({ 255, 255, 255, 255 }), 350, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	officeText->setLayer(1);

	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("oficinafondo");
	fondo->getComponent<Transform>()->setGlobalScale(0.85f, 0.85f);
	//fondo->getComponent<Transform>()->getGlobalScale().set(0.85f, 0.85f);
	fondo->setLayer(0);

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

	//------Boton para deckBuilding:
	ecs::entity_t db = Instantiate();
	db->addComponent<Transform>();
	db->addComponent<SpriteRenderer>("rice");
	db->addComponent<BoxCollider>();
	Vector2D dbPos(500, 10);
	db->getComponent<Transform>()->setGlobalPos(dbPos);
	db->getComponent<Transform>()->setGlobalScale(Vector2D(0.5f, 0.5f));
	db->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	db->addComponent<NPC>(9); // Lleva al deckbuilding (9).
	db->setLayer(1);

	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").play(-1);
	sdl.soundEffects().at("deckbuilder_theme").setChannelVolume(10);


}

void OfficeState::onExit()
{
	std::cout << "\nEXIT OFFICE.\n";

	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").pauseChannel();

	GameStateMachine::instance()->getMngr()->Free();
}

