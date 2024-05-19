#include <../pchs/pch.h>

#include "OfficeState.h"
#include "../components/managers/Manager.h"
#include "../../sdlutils/InputHandler.h"
#include "../components/basics/TextComponent.h"
#include "../factories/Factory.h"
#include "../factories/NPCFactory_V0.h"
#include "../CaseManager.h"
#include "../SoundManager.h"

#include "../components/NPC.h"
#include "game/components/Clickable.h"
#include "game/components/ShineComponent.h"
#include "../TutorialManager.h"
#include "../components/managers/TutorialOfficeManager.h"

OfficeState::OfficeState() :
	factory(nullptr),
	offset_(5)
{
	TuVieja("Loading OfficeState");
	isTutorial = false;
}

OfficeState::OfficeState(bool t) :
	factory(nullptr),
	offset_(5)
{
	isTutorial = t;


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
	factory->SetFactories(static_cast<NPCFactory*>(new NPCFactory_V0()));

	//-----Imagen de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("oficinafondo");
	fondo->getComponent<Transform>()->setGlobalScale(0.5f, 0.55f);
	fondo->setLayer(0);

	//------Boton para volver:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);

	if (GameStateMachine::instance()->TUTORIAL_CITY_COMPLETE()) {
		exit->addComponent<NPC>(GameStates::CITY); // Lleva a la ciudad (1).
	}
	else if (GameStateMachine::instance()->TUTORIAL_DECKBUILDING_COMPLETE()) {
		exit->addComponent<NPC>(GameStates::TUTORIAL_CITY); // Lleva a la ciudad (1).
	}
	else {
		exit->addComponent<NPC>(GameStates::CITY); // Lleva a la ciudad (1).
	}
	exit->setLayer(1);
	exit->addComponent<Clickable>("boton_flecha", true);

	//------Boton para deckBuilding:
	ecs::entity_t db = Instantiate();
	auto dbTrans = db->addComponent<Transform>();
	dbTrans->addParent(fondo->getComponent<Transform>());

	auto dbBox = db->addComponent<BoxCollider>();
	Vector2D dbSiz(550, 500);
	dbBox->setSize(dbSiz);
	dbBox->setPosOffset(Vector2D(30, 0));

	Vector2D dbPos(478, 112);
	dbTrans->setGlobalPos(dbPos);
	if (isTutorial) {
		db->addComponent<NPC>(GameStates::TUTORIAL_DECKBUILDING); // Lleva al deckbuilding TUTORIAL (9).
	}
	else {
		db->addComponent<NPC>(GameStates::DECKBUILDING); // Lleva al deckbuilding (9).
	}

	db->setLayer(1);
	db->addComponent<SpriteRenderer>("pizarra");
	auto dbShine = db->addComponent<ShineComponent>();
	dbShine->addEnt(db->getComponent<SpriteRenderer>(), "pizarra_brilli");

	//------Boton para telefono: (WIP de Poli: El telf en realidad es un NPC invisible,
	//  que al clicarlo hace que aparezca el dialogo.)
	const int caso = getCurrentCase() + offset_;
	ecs::entity_t npc;
	if (caseManager->accepted())
		npc = factory->createNPC(caso, fondo, 1);
	else
		npc = factory->createNPC(caso, fondo);

	caseManager->addNPC(npc);
	objs.push_back(npc);

	//Idea para los casos:
	// - En dialoguesV1.json meter el texto de los casos que queremos que se diga. Como Caso0, Caso1, etc.
	// - En npcs.json crear nuevos npcs para cada caso, los cuales no tendrian sprite, o seria transparente.
	// - Se instanciaria aqui, usando factory->createNPC(getCurrentCase() + offset, fondo), donde el offset
	//   seria el numero de npcs que hay antes en npcs.json

	objs.push_back(db);
	objs.push_back(exit);

	

	setTutorial();


	/// MUSICA
	auto music = SoundManager::instance();
	music->startMusic(Musics::OFFICE_M);
}

void OfficeState::onExit()
{
	std::cout << "\nEXIT OFFICE.\n";

	// se desuscribe al evento
	ih().clearFunction(ih().PAUSEKEY_DOWN, [this] { onPauseOF(); });

	auto music = SoundManager::instance();
	music->stopMusic(Musics::OFFICE_M);

	GameStateMachine::instance()->getMngr()->Free();

	delete factory;
}

void OfficeState::onPauseOF()
{
	SetLastState(2);
	GameStateMachine::instance()->setState(17);
}

void OfficeState::setTutorial()
{
	if (isTutorial) {

		// entidad tutorial para gestionar cositas
		tutorial = Instantiate();

		prepareTutorial();

		tutorial->addComponent<TutorialManager>();
		auto manager = tutorial->addComponent<TutorialOfficeManager>(base, tutorial);
		GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::TUTORIAL_MANAGER, tutorial);


		tutorial->getComponent<TutorialManager>()->startTutorial();
		tutorial->getComponent<TutorialManager>()->setCurrentTutorial(Tutorials::OFFICE);
		tutorial->getComponent<TutorialManager>()->setCurrentTutorialState(Tutorials::Oficina::OFFICE_NONE);
		tutorial->getComponent<TutorialManager>()->setNextTutorialState(Tutorials::Oficina::OFFICE_INIT);


		int a = tutorial->getComponent<TutorialManager>()->getTutorialState();

		tutorial->getComponent<TutorialOfficeManager>()->setObjs(objs);
	}
	else {
		GameStateMachine::instance()->setTUTORIAL_DECKBUILDING_COMPLETE(true);
	}
}

void OfficeState::prepareTutorial()
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

void OfficeState::startTutorial(bool a)
{
	isTutorial = a;
}

