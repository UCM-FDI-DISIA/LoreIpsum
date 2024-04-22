#include <../pchs/pch.h>

#include "OfficeState.h"
#include "../components/managers/Manager.h"
#include "../../sdlutils/InputHandler.h"
#include "../components/basics/TextComponent.h"
#include "../factories/Factory.h"
#include "../factories/NPCFactory_V0.h"

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
	
	factory = new Factory();
	factory->SetFactories(
		static_cast<NPCFactory*>(new NPCFactory_V0())
	);

	//------Texto de la oficina.
	ecs::entity_t officeText = Instantiate(Vector2D(210, 30));
	officeText->addComponent<TextComponent>("OFICINA", "8bit_size_20", SDL_Color({ 255, 255, 255, 255 }), 350, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	officeText->setLayer(1);

	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("oficinafondo");
	fondo->getComponent<Transform>()->setGlobalScale(0.5f, 0.55f);
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
	//db->addComponent<SpriteRenderer>("rice");
	db->addComponent<BoxCollider>();
	Vector2D dbSiz(400, 300);
	db->getComponent<BoxCollider>()->setSize(dbSiz);
	Vector2D dbPos(500, 90);
	db->getComponent<Transform>()->setGlobalPos(dbPos);
	//db->getComponent<Transform>()->setGlobalScale(Vector2D(0.5f, 0.5f));
	//db->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	db->addComponent<NPC>(9); // Lleva al deckbuilding (9).
	db->setLayer(1);

	//------Boton para telefono: (WIP de Poli:  La idea es poner como un NPC invisible (sobre el telefono),
	//  que al clicarlo haga que aparezca el dialogo.)

	factory->createNPC(5, fondo); 

	//Idea para los casos:
	// - En dialoguesV1.json meter el texto de los casos que queremos que se diga. Como Caso0, Caso1, etc.
	// - En npcs.json crear nuevos npcs para cada caso, los cuales no tendrian sprite, o seria transparente.
	// - Se instanciaria aqui, usando factory->createNPC(getCurrentCase() + offset, fondo), donde el offset
	//   seria el numero de npcs que hay antes en npcs.json


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

