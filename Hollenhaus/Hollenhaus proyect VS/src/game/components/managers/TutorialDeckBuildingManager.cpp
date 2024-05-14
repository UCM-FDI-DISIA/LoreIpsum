#include "..\pchs\pch.h"
#include "TutorialDeckBuildingManager.h"
#include "../../TutorialManager.h"
#include "TutorialBaseManager.h"
#include "../../factories/DialogueFactory_V0.h"
#include "../../factories/Factory.h"



TutorialDeckBuilderManager::TutorialDeckBuilderManager(ecs::entity_t b, ecs::entity_t t) 
	: TutorialBaseManager(b, t)
{

}

TutorialDeckBuilderManager::~TutorialDeckBuilderManager()
{
}

void TutorialDeckBuilderManager::initComponent()
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

void TutorialDeckBuilderManager::update()
{
	if (actionEnded()) {

		nextTutorialState();

		resetEnded();
	}

	updateTutorialState();
}

void TutorialDeckBuilderManager::addToHand(ecs::entity_t c)
{
}

void TutorialDeckBuilderManager::setState()
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
	default:
		break;
	}

	currentState = nextState;

	ent_->getComponent<TutorialManager>()->setCurrentTutorialState(t);

	checked = false;
}
