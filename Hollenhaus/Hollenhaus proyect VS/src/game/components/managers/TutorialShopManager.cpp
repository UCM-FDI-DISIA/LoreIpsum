#include "..\pchs\pch.h"
#include "TutorialShopManager.h"

#include "../../TutorialManager.h"
#include "TutorialBaseManager.h"
#include "../../factories/DialogueFactory_V0.h"
#include "../../factories/Factory.h"

TutorialShopManager::TutorialShopManager(ecs::entity_t b, ecs::entity_t t)
	: TutorialBaseManager(b, t)
{
}

TutorialShopManager::~TutorialShopManager()
{
}

void TutorialShopManager::initComponent()
{
	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);

	//currentState = Tutorials::Deckbuilder::DECKBUILDER_NONE;
	//nextState = Tutorials::Deckbuilder::DECKBUILDING_INIT;
	ended = false;
	checked = false;


	image = Instantiate();
	image->addComponent<Transform>();
	image->addComponent<SpriteRenderer>("card_ejemplo");
	image->getComponent<SpriteRenderer>()->enable(false);
}

void TutorialShopManager::update()
{
	if (actionEnded()) {

		nextTutorialState();

		resetEnded();
	}

	updateTutorialState();
}

void TutorialShopManager::setState()
{
	int t = ent_->getComponent<TutorialManager>()->getNextState();
	/*ent_->getComponent<TutorialManager>()->activateColliders(objs);
	ent_->getComponent<TutorialManager>()->resetColliderWall(objs);*/
	image->getComponent<SpriteRenderer>()->enable(false);



	switch (t)
	{
	case Tutorials::Deckbuilder::DECKBUILDING_INIT:

		break;
	case Tutorials::Deckbuilder::PIZARRA:

		break;
	case Tutorials::Deckbuilder::CARDS:

		break;
	case Tutorials::Deckbuilder::DRAWER:

		break;
	default:
		break;
	}

	currentState = nextState;

	ent_->getComponent<TutorialManager>()->setCurrentTutorialState(t);

	checked = false;
}
