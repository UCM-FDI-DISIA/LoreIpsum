#include "../../pch.h"
#include "pch.h"
#include "TutorialBoardManager.h"
#include <SDL.h>
#include "../../components/Drag.h"
#include "../../components/managers/CardStateManager.h"
#include "../../components/managers/DragManager.h"
#include "../../components/managers/Manager.h"
#include "../../../sdlutils/InputHandler.h"
#include "../../factories/Factory.h"
#include "../../factories/DialogueFactory_V0.h"
#include "../../factories/CardFactory_v0.h"
#include "../../factories/CardFactory_v1.h"
#include "../../factories/BoardFactory_v0.h"
#include "../../factories/MatchStateUIFactory_v0.h"
#include "../../components/managers/MatchManager.h"
#include "../../components/managers/BoardManager.h"
#include "../../components/basics/TextComponent.h"
#include "../../components/managers/MatchManager.h"
#include "../../components/EndTurnButton.h"
#include "../../components/NPC.h"

#include "../../components/managers/IA_manager.h"

#include "../../components/managers/Manager.h"
#include "../../GameStateMachine.h"
#include "../../components/managers/PlayerCardsManager.h"
#include "../../TutorialManager.h"

TutorialBoardManager::TutorialBoardManager(ecs::entity_t b, ecs::entity_t t)
{
	base = b;
	tutorial = t;

	// ---
	//objs.push_back(base);
	//objs.push_back(tutorial);

}

TutorialBoardManager::~TutorialBoardManager()
{
	delete factory;
	factory = nullptr;
}

void TutorialBoardManager::initComponent()
{
	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);

	currentState = Tutorials::Board::BOARD_NONE;
	nextState = Tutorials::Board::INIT;
	ended = false;
}


void TutorialBoardManager::update()
{
	if (actionEnded()) {

		nextTutorialState();

		resetEnded();
	}

	updateTutorialState();
}

void TutorialBoardManager::nextTutorialState()
{
	nextState = tutorial->getComponent<TutorialManager>()->nextState();
}

void TutorialBoardManager::updateTutorialState()
{
	currentState;
	nextState;

	if (currentState != nextState) {
		ent_->getComponent<TutorialManager>()->wait([this] { setState(); });
	}
}

bool TutorialBoardManager::actionEnded()
{
	return ent_->getComponent<TutorialManager>()->hasEnded();
}


void TutorialBoardManager::resetEnded()
{
	ent_->getComponent<TutorialManager>()->resetAction();
}

void TutorialBoardManager::setState()
{
	int t = ent_->getComponent<TutorialManager>()->getNextState();
	ent_->getComponent<TutorialManager>()->activateColliders(objs);

	switch (t)
	{
	case Tutorials::Board::INIT:
		setINIT();
		break;
	case Tutorials::Board::CARD:
		setCARD();
		break;
	case Tutorials::Board::DECK:
		setDECK();
		break;
	case Tutorials::Board::DRAW_CARD:
		setDRAWCARD();
		break;
	case Tutorials::Board::CELL:
		setCELL();
		break;
	case Tutorials::Board::PLACE_CARD:
		setPLACECARD();
		break;
	case Tutorials::Board::ACTION:
		setACTION();
		break;
	case Tutorials::Board::NEXT_TURN:
		setNEXTTURN();
		break;
	default:
		break;
	}

	currentState = nextState;

	ent_->getComponent<TutorialManager>()->setCurrentTutorialState(t);
}


ecs::entity_t TutorialBoardManager::createPopUp(float x, float y, std::string popup, int convo)
{
	TuVieja("Creando PopUp...");

	JsonData::DialogueData dialogue = sdlutils().dialogues().at(popup);
	//int conv = 0;
	int node = 0;

	// AQUIIIIIIIIII

	// crear dialogo del FACTORY de dialogos
	//// Mirar comentario en el interior de la función
	ecs::entity_t pop = factory->createDialogue(dialogue.NPCName(), convo, node,
		{ x, y },//POS
		{ 0.25, 0.25 }, //SIZE (poli: no cambia nada?¿)	// Luis: Dentro de createDialogue, size depende del tamaó del sprite, y no es parametrizable
		5, 10, base,
		3, dialogue.Convo(convo).isAuto(),  //LAYER
		"8bit_size_20",	//mirar el JSON para cambiar el tamanio de texto
		SDL_Color({ 0, 0, 0, 255 }),
		220, //wrap length
		Text::BoxPivotPoint::LeftTop,
		Text::TextAlignment::Left);

	return pop;
}

void TutorialBoardManager::setBase(ecs::entity_t b)
{
	base = b;
}

void TutorialBoardManager::setTutorial(ecs::entity_t t)
{
	tutorial = t;
}

void TutorialBoardManager::setObjs(std::vector<ecs::entity_t> v)
{
	objs = v;
}




void TutorialBoardManager::setINIT()
{
	TuVieja("Setting INIT");

	createPopUp(250, 200, "Board Tutorial", 0);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);
}

void TutorialBoardManager::setCARD()
{
	TuVieja("Setting CARD");

	createPopUp(250, 200, "Board Tutorial", 1);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

}

void TutorialBoardManager::setDECK()
{
	TuVieja("Setting DECK");

	ecs::entity_t pop = createPopUp(550, 300, "Board Tutorial", 2);



	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);


}

void TutorialBoardManager::setDRAWCARD()
{

	std::vector<ecs::entity_t> v;

	v.push_back(deck);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->activateColliders(v);
}

void TutorialBoardManager::setCELL()
{
	TuVieja("Setting CELL");

	createPopUp(250, 200, "Board Tutorial", 3);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);
}

void TutorialBoardManager::setPLACECARD()
{
	TuVieja("Setting PLACE CARD");

	createPopUp(250, 200, "Board Tutorial", 4);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);
}

void TutorialBoardManager::setACTION()
{
	TuVieja("Setting PLACE CARD");

	createPopUp(250, 200, "Board Tutorial", 5);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);
}



void TutorialBoardManager::setNEXTTURN()
{
	TuVieja("Setting PLACE CARD");

	//createPopUp(250, 200, "Board Tutorial", 5);

	std::vector<ecs::entity_t> v;

	v.push_back(nextTurn);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->activateColliders(v);

}

