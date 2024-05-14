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

	currentState = Tutorials::Deckbuilder::DECKBUILDER_NONE;
	nextState = Tutorials::Deckbuilder::DECKBUILDING_INIT;
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
	/*ent_->getComponent<TutorialManager>()->activateColliders(objs);
	ent_->getComponent<TutorialManager>()->resetColliderWall(objs);*/
	image->getComponent<SpriteRenderer>()->enable(false);



	switch (t)
	{
	case Tutorials::Deckbuilder::DECKBUILDING_INIT:
		setINIT();
		break;
	case Tutorials::Deckbuilder::PIZARRA:
		setPIZARRA();
		break;
	case Tutorials::Deckbuilder::CARDS:
		setCard();
		break;
	case Tutorials::Deckbuilder::DRAWER:
		setDrawer();
		break;
	default:
		break;
	}

	currentState = nextState;

	ent_->getComponent<TutorialManager>()->setCurrentTutorialState(t);

	checked = false;
}

void TutorialDeckBuilderManager::setINIT()
{
	TuVieja("Setting INIT");


	createPopUp(250, 200, "Deck Tutorial", 0, base);
	std::vector<ecs::entity_t> v;

	/*tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);*/
}

void TutorialDeckBuilderManager::setPIZARRA()
{
	std::cout << "pizarra " << std::endl;

	createPopUp(250, 200, "Deck Tutorial", 1, base);
	std::vector<ecs::entity_t> v;

}

void TutorialDeckBuilderManager::setCard()
{
	std::cout << "card " << std::endl;

	createPopUp(250, 200, "Deck Tutorial", 2, base);
	std::vector<ecs::entity_t> v;

}

void TutorialDeckBuilderManager::setDrawer()
{
	std::cout << "drawer " << std::endl;
	createPopUp(250, 200, "Deck Tutorial", 3, base);
	std::vector<ecs::entity_t> v;

}
