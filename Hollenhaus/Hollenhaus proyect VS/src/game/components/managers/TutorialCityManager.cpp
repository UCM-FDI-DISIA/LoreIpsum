#include "..\pchs\pch.h"
#include "TutorialCityManager.h"

#include "../../TutorialManager.h"
#include "TutorialBaseManager.h"
#include "../../factories/DialogueFactory_V0.h"
#include "../../factories/Factory.h"


TutorialCityManager::TutorialCityManager(ecs::entity_t b, ecs::entity_t t)
	: TutorialBaseManager(b, t)
{


}

TutorialCityManager::~TutorialCityManager()
{
}

void TutorialCityManager::initComponent()
{
	factory = new Factory();
	factory->SetFactories(
		static_cast<DialogueFactory*>(new DialogueFactory_V0())
	);

	currentState = Tutorials::Oficina::OFFICE_NONE;
	nextState = Tutorials::Oficina::OFFICE_INIT;
	ended = false;
	checked = false;
}

void TutorialCityManager::update()
{
	if (actionEnded()) {

		nextTutorialState();

		resetEnded();
	}

	updateTutorialState();
}

void TutorialCityManager::setState()
{

	int t = ent_->getComponent<TutorialManager>()->getNextState();
	ent_->getComponent<TutorialManager>()->activateColliders(objs);
	image->getComponent<SpriteRenderer>()->enable(false);



	switch (t)
	{
	case Tutorials::Ciudad::CITY_INIT:
		setINIT();
		break;
	case Tutorials::Ciudad::CITY_MOVE:
		setMOVE();
		break;
	case Tutorials::Ciudad::CITY_PERSON:
		setINTERACTION();
		break;
	default:
		break;
	}

	currentState = nextState;

	ent_->getComponent<TutorialManager>()->setCurrentTutorialState(t);

	checked = false;
}

void TutorialCityManager::setINIT()
{
	createPopUp(250, 250, "City Tutorial", 0, base);
	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialCityManager::setINTERACTION()
{
	createPopUp(250, 250, "City Tutorial", 0, base);
	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}

void TutorialCityManager::setMOVE()
{
	createPopUp(250, 250, "City Tutorial", 0, base);
	std::vector<ecs::entity_t> v;

	tutorial->getComponent<TutorialManager>()->deactivateColliders(objs);

	tutorial->getComponent<TutorialManager>()->setColliderWall(v, base);
}
