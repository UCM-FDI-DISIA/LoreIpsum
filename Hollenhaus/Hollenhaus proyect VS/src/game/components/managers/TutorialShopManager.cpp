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
	case Tutorials::Tienda::SHOP_INIT:
		setINIT();
		break;
	case Tutorials::Tienda::SHOW_MONEY:
		setSHOW_MONEY();
		break;
	case Tutorials::Tienda::SHOW_CARDS:
		setSHOW_CARDS();
		break;
	case Tutorials::Tienda::PURCHASE:
		setPURCHASE();
		break;
	default:
		break;
	}

	currentState = nextState;

	ent_->getComponent<TutorialManager>()->setCurrentTutorialState(t);

	checked = false;
}

void TutorialShopManager::setINIT()
{
	createPopUp(250, 200, "Tienda Tutorial", 0, base);

}

void TutorialShopManager::setSHOW_MONEY()
{
	createPopUp(250, 200, "Tienda Tutorial", 1, base);

}

void TutorialShopManager::setSHOW_CARDS()
{
	createPopUp(250, 200, "Tienda Tutorial", 2, base);

}

void TutorialShopManager::setPURCHASE()
{
	createPopUp(250, 200, "Tienda Tutorial", 3, base);

}
