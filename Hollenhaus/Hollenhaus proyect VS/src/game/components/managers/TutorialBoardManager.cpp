#include <../pchs/pch.h>
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
	: TutorialBaseManager(b,t)
{

}

TutorialBoardManager::~TutorialBoardManager()
{
	;
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
	checked = false;


	image = Instantiate();
	image->addComponent<Transform>();
	image->addComponent<SpriteRenderer>("card_ejemplo");
	image->getComponent<SpriteRenderer>()->enable(false);

	

}


void TutorialBoardManager::update()
{
	if (actionEnded()) {

		nextTutorialState();

		resetEnded();
	}

	updateTutorialState();
	
}

void TutorialBoardManager::addToHand(ecs::entity_t c)
{
	std::vector<ecs::entity_t> v;

	hand.push_back(c);

	v.push_back(c);

	setLayers(v);
}

void TutorialBoardManager::setState()
{
	int t = ent_->getComponent<TutorialManager>()->getNextState();
	ent_->getComponent<TutorialManager>()->activateColliders(objs);
	ent_->getComponent<TutorialManager>()->resetColliderWall(objs);
	image->getComponent<SpriteRenderer>()->enable(false);


	switch (t)
	{
	case Tutorials::Board::INIT:
		setINIT();
		break;
	case Tutorials::Board::CARD:
		setCARD();
		break;
	case Tutorials::Board::CARD_COST:
		setCARDCOST();
		break;
	case Tutorials::Board::CARD_POINTS:
		setCARDPOINTS();
		break;
	case Tutorials::Board::CARD_IMAGE:
		setCARDIMAGE();
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
	case Tutorials::Board::POINTS:
		setPOINTS();
		break;
	case Tutorials::Board::ACTION:
		setACTION();
		break;
	case Tutorials::Board::ACTION_PTS:
		setACTIONPTS();
		break;
	case Tutorials::Board::NEXT_TURN:
		setNEXTTURN();
		break;
	case Tutorials::Board::PRESS_NEXT_TURN:
		setPRESSNEXTTURN();
		break;
	case Tutorials::Board::AI_TURN:
		setAI_TURN();
		break;
	case Tutorials::Board::NEXT_CARD_1:
		setNEXTCARD1();
		break;
	case Tutorials::Board::EFFECTS_PT1:
		setEFFECTS1();
		break;
	case Tutorials::Board::END_TUTORIAL:
		setENDTUTORIAL();
		break;
	case Tutorials::Board::FREEDOM:
		setFREEDOM();
		break;
	default:
		break;
	}

	currentState = nextState;

	ent_->getComponent<TutorialManager>()->setCurrentTutorialState(t);

	checked = false;

}


void TutorialBoardManager::setINIT()
{
	//TuVieja("Setting INIT");

	createPopUp(250, 200, "Board Tutorial", 0);
	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialBoardManager::setCARD()
{
	//TuVieja("Setting CARD");

	createPopUp(500, 250, "Board Tutorial", 1);

	image->getComponent<SpriteRenderer>()->enable(true);
	image->getComponent<Transform>()->setGlobalPos(325, 200);
	image->getComponent<Transform>()->setGlobalScale(1.25, 1.25);
	image->setLayer(200);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);

}

void TutorialBoardManager::setCARDCOST()
{
	//TuVieja("Setting DECK");

	ecs::entity_t pop = createPopUp(500, 200, "Board Tutorial", 2);

	image->addComponent<SpriteRenderer>("card_ejemplo");
	image->getComponent<Transform>()->setGlobalPos(325, 200);
	image->getComponent<Transform>()->setGlobalScale(1.25, 1.25);

	image->setLayer(200);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialBoardManager::setCARDPOINTS()
{
	//TuVieja("Setting DECK");

	ecs::entity_t pop = createPopUp(500, 300, "Board Tutorial", 3);

	image->addComponent<SpriteRenderer>("card_ejemplo");
	image->getComponent<Transform>()->setGlobalPos(325, 200);
	image->getComponent<Transform>()->setGlobalScale(1.25, 1.25);

	image->setLayer(200);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);

}

void TutorialBoardManager::setCARDIMAGE()
{

	//TuVieja("Setting DECK");

	ecs::entity_t pop = createPopUp(500, 250, "Board Tutorial", 4);

	image->addComponent<SpriteRenderer>("card_ejemplo");
	image->getComponent<Transform>()->setGlobalPos(325, 200);
	image->getComponent<Transform>()->setGlobalScale(1.25, 1.25);

	image->setLayer(200);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialBoardManager::setDECK()
{
	//TuVieja("Setting DECK");

	ecs::entity_t pop = createPopUp(525, 300, "Board Tutorial", 5);



	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);


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
	//TuVieja("Setting CELL");


	std::vector<ecs::entity_t> v;

	createPopUp(250, 200, "Board Tutorial", 6);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(hand);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);


	
}

void TutorialBoardManager::setPLACECARD()
{
	//TuVieja("Setting PLACE CARD");

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	std::vector<ecs::entity_t> v;

	for (auto h : hand) {
		v.push_back(h);
	}

	tutorial->getComponent<TutorialManager>()->activateColliders(v);

}

void TutorialBoardManager::setPOINTS()
{
	//TuVieja("Setting PLACE CARD");

	createPopUp(250, 200, "Board Tutorial", 7);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialBoardManager::setACTION()
{
	//TuVieja("Setting PLACE CARD");

	createPopUp(250, 200, "Board Tutorial", 8);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialBoardManager::setACTIONPTS()
{
	//TuVieja("Setting PLACE CARD");

	createPopUp(250, 200, "Board Tutorial", 9);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialBoardManager::setNEXTTURN()
{
	std::vector<ecs::entity_t> v;

	createPopUp(250, 200, "Board Tutorial", 10);

	//v.push_back(nextTurn);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);

	//tutorial->getComponent<TutorialManager>()->activateColliders(v);

}

void TutorialBoardManager::setPRESSNEXTTURN()
{
	std::vector<ecs::entity_t> v;

	v.push_back(nextTurn);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->activateColliders(v);

}

void TutorialBoardManager::setAI_TURN()
{
	std::vector<ecs::entity_t> v;

	createPopUp(250, 200, "Board Tutorial", 11);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);


}

void TutorialBoardManager::setNEXTCARD1()
{
	std::vector<ecs::entity_t> v;

	createPopUp(250, 200, "Board Tutorial", 12);

	//tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialBoardManager::setEFFECTS1()
{
	std::vector<ecs::entity_t> v;

	createPopUp(250, 200, "Board Tutorial", 13);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialBoardManager::setENDTUTORIAL()
{
	std::vector<ecs::entity_t> v;

	createPopUp(250, 200, "Board Tutorial", 14);

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialBoardManager::setFREEDOM()
{
	std::cout << "LIBERTAD OMFG" << std::endl;


	// FIN DEL TUTO
	GameStateMachine::instance()->setTUTORIAL_BOARD_COMPLETE(true);

}

