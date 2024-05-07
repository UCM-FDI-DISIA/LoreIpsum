#include <../pchs/pch.h>

#include "OfficeState.h"
#include "../components/managers/Manager.h"
#include "../../sdlutils/InputHandler.h"
#include "../components/basics/TextComponent.h"
#include "../factories/Factory.h"
#include "../factories/NPCFactory_V0.h"
#include "../CaseManager.h"

#include "../components/NPC.h"
#include "game/components/Clickable.h"
#include "game/components/ShineComponent.h"


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

	// llamada al input
	ih().insertFunction(ih().PAUSEKEY_DOWN, [this] { onPauseOF(); });

	CaseManager* caseManager = GameStateMachine::instance()->caseMngr();
	
	factory = new Factory();
	factory->SetFactories(
		static_cast<NPCFactory*>(new NPCFactory_V0())
	);

	//------Texto de la oficina.
	//ecs::entity_t officeText = Instantiate(Vector2D(210, 30));
	//officeText->addComponent<TextComponent>("OFICINA", "8bit_size_20", SDL_Color({ 255, 255, 255, 255 }), 350, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	//officeText->setLayer(1);

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
		exit->addComponent<Clickable>("boton_flecha", true);



	//------Boton para deckBuilding:
	ecs::entity_t db = Instantiate();
	auto dbTrans = db->addComponent<Transform>();
	dbTrans->addParent(fondo->getComponent<Transform>());

	db->addComponent<BoxCollider>();
	Vector2D dbSiz(400, 300);
	db->getComponent<BoxCollider>()->setSize(dbSiz);

	Vector2D dbPos(478, 112);
	dbTrans->setGlobalPos(dbPos);

	db->addComponent<NPC>(9); // Lleva al deckbuilding (9).
	db->setLayer(1);
	db->addComponent<SpriteRenderer>("pizarra");
	auto dbShine = db->addComponent<ShineComponent>();
	dbShine->addEnt(db->getComponent<SpriteRenderer>(), "pizarra_brilli");
	


	/// tfno
	ecs::entity_t tfno = Instantiate();
	auto tfnoTrans = tfno->addComponent<Transform>();
	tfnoTrans->addParent(fondo->getComponent<Transform>());

	tfno->addComponent<BoxCollider>();
	Vector2D tfnoSiz(400, 300);
	tfno->getComponent<BoxCollider>()->setSize(tfnoSiz);

	Vector2D tfnoPos(478, 112);
	dbTrans->setGlobalPos(tfnoPos);

	tfno->addComponent<NPC>(9); // Lleva al deckbuilding (9).
	tfno->setLayer(1);
	tfno->addComponent<SpriteRenderer>("tfno");
	auto tfnoShine = tfno->addComponent<ShineComponent>();
	tfnoShine->addEnt(tfno->getComponent<SpriteRenderer>(), "tfno_brilli");






	//------Boton para telefono: (WIP de Poli: El telf en realidad es un NPC invisible,
	//  que al clicarlo hace que aparezca el dialogo.)

	if(caseManager->accepted())
		caseManager->addNPC(factory->createNPC(6, fondo, 1));
	else
		caseManager->addNPC(factory->createNPC(6, fondo));

	//Idea para los casos:
	// - En dialoguesV1.json meter el texto de los casos que queremos que se diga. Como Caso0, Caso1, etc.
	// - En npcs.json crear nuevos npcs para cada caso, los cuales no tendrian sprite, o seria transparente.
	// - Se instanciaria aqui, usando factory->createNPC(getCurrentCase() + offset, fondo), donde el offset
	//   seria el numero de npcs que hay antes en npcs.json


	/// MUSICA
	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").play(-1);
	sdl.soundEffects().at("deckbuilder_theme").setChannelVolume(10);
}

void OfficeState::onExit()
{
	std::cout << "\nEXIT OFFICE.\n";

	// se desuscribe al evento
	ih().clearFunction(ih().PAUSEKEY_DOWN, [this] { onPauseOF(); });

	auto& sdl = *SDLUtils::instance();
	sdl.soundEffects().at("deckbuilder_theme").pauseChannel();

	GameStateMachine::instance()->getMngr()->Free();

	delete factory;
}

void OfficeState::onPauseOF()
{
	SetLastState(2);
	GameStateMachine::instance()->setState(17);
}

